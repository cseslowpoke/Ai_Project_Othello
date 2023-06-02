#include<string>
class ai{
  public:
    int player;
    ai(int _player) {
      player = _player;
    }
    virtual int move(std::string board) = 0;  
};