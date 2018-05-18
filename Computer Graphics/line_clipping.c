#include <stdio.h>
#include <graphics.h>


typedef struct coordinate
{
    int x, y;
    char code[4];
} PT;

// coordinates of the window
PT w1, w2, w3, w4;

void draw_window() {
    line(w1.x, w1.y, w2.x, w2.y);
    line(w2.x, w2.y, w3.x, w3.y);
    line(w3.x, w3.y, w4.x, w4.y);
    line(w4.x, w4.y, w1.x, w1.y);
}

void draw_line(PT p1, PT p2) {
    line(p1.x, p1.y, p2.x, p2.y);
}

PT set_code(PT p) {
    if(p.y < w1.y)
        p.code[0]='1';    //Top
    else
        p.code[0]='0';
    
    if(p.y > w3.y)
        p.code[1]='1';    //Bottom
    else
        p.code[1]='0';
        
    if(p.x > w2.x)
        p.code[2]='1';    //Right
    else
        p.code[2]='0';
        
    if(p.x < w1.x)
        p.code[3]='1';    //Left
    else
        p.code[3]='0';
    
    return(p);
}

int is_visible(PT p1, PT p2) {
    int flag = 0;

    // check if code for both points is zero
    for(int i=0; i < 4; i++) {
        if(p1.code[i] != '0' || p2.code[i] != '0') {
            flag = 1;
            break;
        }
    }

    if(flag == 0)
        return 0;
    
    // check if logical AND of both points is not zero
    for(int i=0; i < 4; i++) {
        if(p1.code[i] == p2.code[i] && p1.code[i] == '1') {
            flag = 0;
            break;
        }
    }

    if(flag == 0)
        return 1;
    
    return 2;
}

PT get_intersection(PT p1, PT p2) {
    PT temp;
    int x, y;
    float m, k;

    if(p1.code[2] == '1')  // Right intersection
        x = w2.x;
    else if(p1.code[3] == '1')  // Left intersection
        x = w1.x;

    if(p1.code[2] == '1' || p1.code[3] == '1') {
        m = (float) (p2.y - p1.y) / (p2.x - p1.x);  // slope of line
        k = p1.y + m * (x - p1.x);  // equation of line
        temp.y = k;
        temp.x = x;
        
        for(int i=0; i < 4; i++)
            temp.code[i] = p1.code[i];
        
        if(temp.y <= w3.y && temp.y >= w1.y)
            return temp;
    }
    
    if(p1.code[0] == '1')  // Top intersection
        y = w1.y;
    else if(p1.code[1] == '1')  // Bottom intersection
        y = w3.y;

    if(p1.code[0] == '1' || p1.code[1] == '1') {
        m = (float) (p2.y - p1.y) / (p2.x - p1.x);  // slope of line
        k = (float)p1.x + (float)(y - p1.y) / m;  // equation of line
        temp.x = k;
        temp.y = y;
        
        for(int i=0; i < 4; i++)
            temp.code[i] = p1.code[i];
        
        return temp;
    }

    return p1;
}

void line_clip(PT p1, PT p2) {
    // display original line
    draw_window();
    delay(500);
    draw_line(p1, p2);
    delay(1000);
    cleardevice();
    delay(500);

    // perform clipping
    PT p3, p4;
    p1 = set_code(p1);
    p2 = set_code(p2);
    int v = is_visible(p1, p2);
    draw_window();
    delay(500);
    switch(v) {
        case 0:  // line is completely inside the window
        draw_line(p1, p2);
        break;

        case 1:  // line is completely outside the window
        break;

        case 2:  // line is intesecting the window
        p3 = get_intersection(p1, p2);
        p4 = get_intersection(p2, p1);
        draw_line(p3, p4);
        break;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Initialize coordinates of the window
    w1.x = 150; w1.y = 100;
    w2.x = 450; w2.y = 100;
    w3.x = 450; w3.y = 350;
    w4.x = 150; w4.y = 350;

    // Line points
    PT p1, p2;
    p1.x = 100; p1.y = 200;
    p2.x = 400; p2.y = 50;

    line_clip(p1, p2);

    delay(3000);
    closegraph();
    return 0;
}
