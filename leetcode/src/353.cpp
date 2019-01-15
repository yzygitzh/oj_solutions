class SnakeGame {
public:
    /** Initialize your data structure here.
        @param width - screen width
        @param height - screen height 
        @param food - A list of food positions
        E.g food = [[1,1], [1,0]] means the first food is positioned at [1,1], the second is at [1,0]. */
    
    vector<vector<int>> occupied;
    list<pair<int, int>> snake;
    queue<pair<int, int>> foods;
    int width, height;
    int score;
    
    SnakeGame(int _width, int _height, vector<pair<int, int>> _food) {
        width = _width;
        height = _height;
        for (auto itr = _food.begin(); itr != _food.end(); ++itr) {
            foods.push(*itr);
        }
        snake.push_back(make_pair(0, 0));
        occupied = vector<vector<int>>(height, vector<int>(width, 0));
        occupied[0][0] = 1;
        score = 0;
    }
    
    /** Moves the snake.
        @param direction - 'U' = Up, 'L' = Left, 'R' = Right, 'D' = Down 
        @return The game's score after the move. Return -1 if game over. 
        Game over when snake crosses the screen boundary or bites its body. */
    int move(string direction) {
        pair<int, int> head = snake.front(), newHead = head, back = snake.back();
        
        if (direction == "U") newHead.first -= 1;
        else if (direction == "L") newHead.second -= 1;
        else if (direction == "R") newHead.second += 1;
        else (newHead.first) += 1;
        
        if (newHead.first < 0 || newHead.first >= height ||
            newHead.second < 0 || newHead.second >= width) {
            return -1;
        }
        
        if (!foods.empty() &&
            foods.front().first == newHead.first &&
            foods.front().second == newHead.second) {
            foods.pop();
            score++;
        } else {
            snake.pop_back();
            occupied[back.first][back.second] = 0;
        }
        
        if (occupied[newHead.first][newHead.second]) return -1;
        snake.push_front(newHead);
        occupied[newHead.first][newHead.second] = 1;
        
        return score;
    }
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame obj = new SnakeGame(width, height, food);
 * int param_1 = obj.move(direction);
 */