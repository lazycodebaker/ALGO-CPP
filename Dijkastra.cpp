#include "SFML/Graphics.hpp"
#include "iostream"
#include "vector"
#include "queue"
#include "random"
#include "limits"

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int CELL_SIZE = 20;
const int GRID_WIDTH = WINDOW_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;
const int INF = numeric_limits<int>::max();

enum CellType {
    EMPTY,
    WALL
};

struct Cell {
    int x, y;
    CellType type;
    bool visited;
    int distance;
    pair<int, int> prev;

    Cell(int _x, int _y, CellType _type = EMPTY) : x(_x), y(_y), type(_type), visited(false), distance(INF) {}

    bool operator<(const Cell& other) const {
        return distance > other.distance;
    }
};

class GridMap {
private:
    vector<vector<Cell>> cells;

public:
    GridMap() {
        cells.resize(GRID_HEIGHT, vector<Cell>(GRID_WIDTH));
    }

    void generateRandomMap() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 1);

        for (int i = 0; i < GRID_HEIGHT; ++i) {
            for (int j = 0; j < GRID_WIDTH; ++j) {
                cells[i][j] = Cell(j, i, dis(gen) ? EMPTY : WALL);
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < GRID_HEIGHT; ++i) {
            for (int j = 0; j < GRID_WIDTH; ++j) {
                sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                rect.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                if (cells[i][j].type == WALL)
                    rect.setFillColor(sf::Color::Black);
                else
                    rect.setFillColor(sf::Color::White);
                window.draw(rect);
            }
        }
    }

    bool isValid(int x, int y) {
        return x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT && cells[y][x].type != WALL;
    }

    vector<pair<int, int>> getNeighbours(int x, int y) {
        vector<pair<int, int>> neighbours;
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (isValid(nx, ny))
                neighbours.push_back({nx, ny});
        }

        return neighbours;
    }

    void dijkstra(pair<int, int> start, pair<int, int> end) {
        priority_queue<Cell> pq;
        cells[start.second][start.first].distance = 0;
        pq.push(cells[start.second][start.first]);

        while (!pq.empty()) {
            Cell current = pq.top();
            pq.pop();

            if (current.visited)
                continue;

            current.visited = true;

            if (current.x == end.first && current.y == end.second)
                return;

            vector<pair<int, int>> neighbours = getNeighbours(current.x, current.y);
            for (const auto& neighbour : neighbours) {
                Cell& next = cells[neighbour.second][neighbour.first];
                int newDistance = current.distance + 1;
                if (newDistance < next.distance) {
                    next.distance = newDistance;
                    next.prev = {current.x, current.y};
                    pq.push(next);
                }
            }
        }
    }

    void drawPath(sf::RenderWindow& window, pair<int, int> start, pair<int, int> end) {
        pair<int, int> current = end;
        while (current != start) {
            sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            rect.setPosition(current.first * CELL_SIZE, current.second * CELL_SIZE);
            rect.setFillColor(sf::Color::Blue);
            window.draw(rect);
            current = cells[current.second][current.first].prev;
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Dijkstra's Algorithm Visualization");
    window.setFramerateLimit(60);

    GridMap map;
    map.generateRandomMap();

    pair<int, int> start(0, 0);
    pair<int, int> end(GRID_WIDTH - 1, GRID_HEIGHT - 1);

    map.dijkstra(start, end);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        map.draw(window);
        map.drawPath(window, start, end);
        window.display();
    }

    return 0;
};