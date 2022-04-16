#include <bangtal.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

SceneID scene1, scene2;
ObjectID title, start_button, end_button, goalkeeper, left_button, right_button, soccerball, Goal, restart_button;
TimerID timer1;


int goalkeeperx = 590;
int goalkeepery = 200;
int count;
int opportunity = 3;
bool goalkeeperbool, soccerballbool;

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown)
{
    ObjectID object = createObject(image);
    locateObject(object, scene, x, y);

    if (shown)
    {
        showObject(object);
    }
    return object;
}

void goalKeeper()
{
    if (rand() % 2 == 0)
    {
        goalkeeperbool = 0;
        goalkeeperx = 200;
        goalkeepery = 200;
    }
    if (rand() % 2 == 1)
    {
        goalkeeperbool = 1;
        goalkeeperx = 1000;
        goalkeepery = 200;
    }
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{
    if (object == start_button)
    {
        hideObject(title);
        hideObject(start_button);
        hideObject(end_button);
        
        enterScene(scene2);
        showMessage("기회는 총 3번입니다");
    }
    if (object == end_button)
    {
        endGame();
    }
    if (object == left_button)
    {
        goalKeeper();
        locateObject(goalkeeper, scene2, goalkeeperx, goalkeepery);
        soccerballbool = 0;
        locateObject(soccerball, scene2, 200, 200);
        showObject(soccerball);
        if (soccerballbool == goalkeeperbool)
        {
            setObjectImage(Goal, "no goal.png");
            showObject(Goal);
            opportunity--;
            if (opportunity == 0)
            {
                char buff[15];
                sprintf_s(buff, 15, "%d 득점!", count);
                showMessage(buff);
                showObject(restart_button);
                hideObject(left_button);
                hideObject(right_button);
                locateObject(end_button, scene2, 590, 30);
                showObject(end_button);
            }
        }
        else if (soccerballbool != goalkeeperbool)
        {
            setObjectImage(Goal, "goal.png");
            showObject(Goal);
            count++;
            opportunity--;
            if (opportunity == 0)
            {
                char buff[15];
                sprintf_s(buff, 15, "%d 득점!", count);
                showMessage(buff);
                showObject(restart_button);
                hideObject(left_button);
                hideObject(right_button);
                locateObject(end_button, scene2, 590, 30);
                showObject(end_button);
            }
        }
        setTimer(timer1, 1.0f);
        startTimer(timer1);
        hideObject(left_button);
        hideObject(right_button);
    }
    if (object == right_button)
    {
        goalKeeper();
        locateObject(goalkeeper, scene2, goalkeeperx, goalkeepery);
        soccerballbool = 1;
        locateObject(soccerball, scene2, 900, 200);
        showObject(soccerball);
        if (soccerballbool == goalkeeperbool)
        {
            setObjectImage(Goal, "no goal.png");
            showObject(Goal);
            opportunity--;
            if (opportunity == 0)
            {
                char buff[15];
                sprintf_s(buff, 15, "%d 득점!", count);
                showMessage(buff);
                showObject(restart_button);
                hideObject(left_button);
                hideObject(right_button);
                locateObject(end_button, scene2, 590, 30);
                showObject(end_button);
            }
        }
        else if (soccerballbool != goalkeeperbool)
        {
            setObjectImage(Goal, "goal.png");
            showObject(Goal);
            count++;
            opportunity--;
            if (opportunity == 0)
            {
                char buff[15];
                sprintf_s(buff, 15, "%d 득점!", count);
                showMessage(buff);
                showObject(restart_button);
                hideObject(left_button);
                hideObject(right_button);
                locateObject(end_button, scene2, 590, 30);
                showObject(end_button);
            }
        }
        setTimer(timer1, 1.0f);
        startTimer(timer1);
        hideObject(left_button);
        hideObject(right_button);
    }
    if (object == restart_button)
    {
        count = 0;
        opportunity = 3;
        showObject(left_button);
        showObject(right_button);
        hideObject(soccerball);
        hideObject(restart_button);
        hideObject(end_button);
        locateObject(goalkeeper, scene2, 590, 200);
    }
}

void timerCallback(TimerID timer)
{
    if (timer == timer1)
    {
        if (opportunity > 0) 
        {
            locateObject(goalkeeper, scene2, 590, 200);
            hideObject(soccerball);
            showObject(left_button);
            showObject(right_button);
            hideObject(Goal);
        }
    }
}

int main()
{

    srand(time(NULL));
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);

    setMouseCallback(mouseCallback);
    setTimerCallback(timerCallback);

    scene1 = createScene("축구 게임", "soccer.jpeg");
    scene2 = createScene("축구 게임", "soccer1.jpeg");

    title = createObject("title.png", scene1, 200, 550, true);

    start_button = createObject("start.png", scene1, 590, 70, true);
    end_button = createObject("end.png", scene1, 590, 30, true);

    goalkeeper = createObject("goalkeeper.png", scene2, goalkeeperx, goalkeepery, true);
    left_button = createObject("left.png", scene2, 570, 70, true);
    right_button = createObject("right.png", scene2, 650, 70, true);

    soccerball = createObject("soccerball.png");
    Goal = createObject("goal.png", scene2, 530, 500, false);
    restart_button = createObject("restart.png", scene2, 590, 70, false);

    timer1 = createTimer(1.0f);

    startGame(scene1);
}