#pragma once

class Star {

    public:
        Star(int x, int y, float speed);

        void update();
        void draw();

    private:
        int posX;
        int posY;
        float speed;

};