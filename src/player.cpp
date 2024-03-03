#include <iostream>
#include <map>
#include <string.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>

#include "player.hpp"

#define RESET "\e[0m"
#define BOLD_ITALIC "\e[3m\e[1m"
#define RED "\e[31m"

#define CHK(op)                                                                \
    if ((op) == -1)                                                            \
        std::perror(#op);

enum Pipe { READ, WRITE };

Player::Player(std::string const &name, Color const color,
               PlayerType const type)
    : _name(name), _color(color), type(type)
{}

std::string const &Player::name() const
{
    return _name;
}

Color Player::color() const
{
    return _color;
}

Human::Human(std::string const name, Color const color)
    : Player(name, color, HUMAN)
{}

bool Human::check(std::string &uci)
{
    // Transform castling notation into UCI
    if (uci == "O-O")
        uci = (color() == WHITE) ? "e1g1" : "e8g8";
    else if (uci == "O-O-O")
        uci = (color() == WHITE) ? "e1c1" : "e8c8";

    try {
        Move move(uci);
        return true;
    }
    catch (std::exception const &e) {
        std::cerr << RED << e.what() << RESET << std::endl;
        return false;
    }
}

ResponseStatus Human::wait_move(Position const &position)
{
    std::string uci;
    do {
        std::cout << BOLD_ITALIC << _name << ", enter your move: " << RESET;
        std::cin >> uci;
        if (uci == "/quit")
            return ResponseStatus{QUIT};
        if (uci == "/cancel")
            return ResponseStatus{CANCEL};
        if (uci == "/draw")
            return ResponseStatus{DRAW};
        if (uci == "/resign")
            return ResponseStatus{RESIGN};
    }
    while (!check(uci));

    return ResponseStatus{MOVE, uci};
}

PieceType Human::wait_promotion()
{
    std::map<char, PieceType> map = {
        {'Q', QUEEN}, {'R', ROOK}, {'B', BISHOP}, {'N', KNIGHT}};
    char p;
    while (true) {
        std::cout << "Promote to (Q/R/B/N): ";
        std::cin >> p;
        if (map.find(p) != map.end())
            return map[p];
        std::cout << "Invalid promotion." << std::endl;
    }
}

Engine::Engine(std::string const name, Color const color)
    : Player(name, color, ENGINE)
{
    CHK(pipe(_engine));
    CHK(pipe(_cli));

    switch (_pid = fork()) {
    case -1:
        throw std::runtime_error("fork() failed");
    case 0:
        dup2(_engine[READ], STDIN_FILENO);
        dup2(_cli[WRITE], STDOUT_FILENO);
        execl("Stockfish/src/stockfish", "stockfish", NULL);
        throw std::runtime_error("execl() failed");
    default:
        close(_cli[WRITE]);
        close(_engine[READ]);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // Send uci command
        write(_engine[WRITE], "uci\n", 4);
    }
}

Engine::~Engine()
{
    CHK(close(_cli[READ]));
    CHK(close(_engine[WRITE]));
    CHK(kill(_pid, SIGKILL));
    waitpid(_pid, NULL, 0);
}

static std::string readline(int fd)
{
    char buf[1024];
    int i = 0;
    int n;
    while ((n = read(fd, &buf[i], sizeof(char))) > 0) {
        if (buf[i++] == '\n')
            return std::string(buf);
    }
    CHK(n);
    return std::string(buf);
}

ResponseStatus Engine::wait_move(Position const &position)
{
    // Send position
    std::string fen = position.to_fen();
    CHK(write(_engine[WRITE], "position fen ", 13));
    CHK(write(_engine[WRITE], fen.c_str(), fen.size()));
    CHK(write(_engine[WRITE], "\n", 1));
    // Send go command
    CHK(write(_engine[WRITE], "go depth 10\n", 12));

    // Read bestmove
    std::string line;
    while (!(line = readline(_cli[READ])).empty()) {
        if (line.starts_with("bestmove"))
            return ResponseStatus{MOVE, line.substr(9, 4)};
    }
    throw std::runtime_error("Engine cannnot find a move.");
}
