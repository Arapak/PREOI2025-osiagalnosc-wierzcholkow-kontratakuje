#include "owklib.h"

#include "communication.h"

namespace {

constexpr int MAX_N = 1e4;
constexpr int MAX_M = 2e4;

int n;
std::vector<std::pair<int, int>> edgesA;
std::vector<std::pair<int, int>> edgesB;

void readInput() {
    int A, B;
    std::cin >> n >> A >> B;
    edgesA.resize(A);
    for (auto &[x, y] : edgesA) std::cin >> x >> y;
    edgesB.resize(B);
    for (auto &[x, y] : edgesB) std::cin >> x >> y;
}

}  // namespace

std::string printData(const DATA_TYPE &data) {
    std::stringstream s;
    s << data;
    return s.str();
}

template <>
void Child::run<CHILD_A>() {
    mainA(n, edgesA);
}

template <>
void Child::run<CHILD_B>() {
    mainK(n, edgesB);
}

void answer(ANSWER_TYPE x) { Child::answer(x); }
void send(DATA_TYPE b) { Child::userSend(b); }
DATA_TYPE receive() { return Child::userReceive<DATA_TYPE>(); }

int main() {
    readInput();

    createPipes();
    forkAndRunChildren();

    try {
        auto [answer, messages, _] = Master::masterMain();
        if ((int)answer.size() != n) {
            printExitMessage(ExitType::ERROR, "WRONG_ANSWER_SIZE");
            return 0;
        }
        printExitMessage(ExitType::ANSWER, messages);
        for (int i = 0; i < n; i++) {
            if (i != 0) std::cout << ' ';
            std::cout << answer[i];
        }
        std::cout << '\n';
    } catch (const CommunicationError &e) {
        panic(ErrorType::COMMUNICATION_ERROR);
    }
    return 0;
}
