#include <iostream>
#include <Windows.h>
#include "backend.h"
#include "help.h"
using namespace std;

void draw_board(int array[][8])
{
    Grid();
    int x1 = 110, y1 = 110, x2 = 190, y2 = 190;
    for (int i = 0; i < 8; i++, y1 += 100, y2 += 100)
    {
        x1 = 110;
        x2 = 190;
        for (int j = 0; j < 8; j++, x1 += 100, x2 += 100)
        {
            if (array[i][j] == 0)
            {
                myEllipse(x1, y1, x2, y2, 255, 0, 100);
            }
            else if (array[i][j] == 1)
            {
                pyramid(x1, y1, x2, y2, 100, 255, 0);
            }

            else if (array[i][j] == 2)
            {
                triangle(x1, y1, x2, y2, 255, 100, 0);
            }

            else if (array[i][j] == 3)
            {
                myRect(x1, y1, x2, y2, 0, 255, 255);
            }

            else if (array[i][j] == 4)
            {
                octagon(x1, y1, x2, y2, 255, 255, 0);
            }

            else if (array[i][j] == 10)
            {
                myEllipse(x1, y1, x2, y2, 255, 255, 255);
            }
            else if (array[i][j] == 11)
            {
                pyramid(x1, y1, x2, y2, 255, 255, 255);
            }

            else if (array[i][j] == 12)
            {
                triangle(x1, y1, x2, y2, 255, 255, 255);
            }

            else if (array[i][j] == 13)
            {
                myRect(x1, y1, x2, y2, 255, 255, 255);
            }

            else if (array[i][j] == 14)
            {
                octagon(x1, y1, x2, y2, 255, 255, 0);
            }

            else if (array[i][j] >= 20)
            {
                myLine(x1, y1, x2, y2, 255, 255, 255);
            }
        }
    }
}

int main()
{
    int array[8][8];
    // Generate random values in the game
    board_generate(array);
    int score = 0;
    int wakat = 200;
    int i = 0;
    int j = 0;
    int x1 = 110, y1 = 110, x2 = 190, y2 = 190;
    cursor(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 255, 255, 255);
    draw_board(array); // DRAWS BOARD
    while (96)
    {
        //! SCORES
        while (cross_clear(array))
        {
            system("cls");
            draw_board(array);
            score += 800;
        }
        while (radius_clear_check(array))
        {
            system("cls");
            draw_board(array);
            score += 60;
        }
        while (vertical_five(array))
        {
            system("cls");
            draw_board(array);
            score += 40;
        }
        while (horizontal_five(array))
        {
            system("cls");
            draw_board(array);
            score += 40;
        }
        while (vertical_four(array, score))
        {
            system("cls");
            draw_board(array);
            score += 10;
        }
        while (horizontal_four(array, score))
        {
            system("cls");
            draw_board(array);
            score += 10;
        }
        while (vertical_three(array))
        {
            system("cls");
            draw_board(array);
            score += 30;
        }
        while (horizontal_three(array))
        {
            system("cls");
            draw_board(array);
            score += 30;
        }

        if (wakat < 0)
        {
            system("cls");
            cout << "Your Game is Over!\n";
            cout << "Well Played!\n";
            cout << "You scored: " << score << endl;
            Sleep(10000);
            break;
        }

        if (wakat >= 0)
        {
			gotoxy(0,0);
			draw_board(array);
			cursor(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 255, 255, 255);
            cout << wakat << " ";
            Sleep(200);
            int key_check;
            while (isCursorKeyPressed(key_check))
            {
                if (key_check == 1) // LEFT
                {
                    if (j > 0)
                    {
                        cursorclear(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 0, 0, 0);
                        x1 -= 100;
                        x2 -= 100;
                        j--;
                        cursor(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 255, 255, 255);
                    }
                }
                else if (key_check == 3) // RIGHT
                {
                    if (j < 7)
                    {
                        cursorclear(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 0, 0, 0);
                        x1 += 100;
                        x2 += 100;
                        j++;
                        cursor(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 255, 255, 255);
                    }
                }
                else if (key_check == 2) // UP
                {
                    if (i > 0)
                    {
                        cursorclear(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 0, 0, 0);
                        y1 -= 100;
                        y2 -= 100;
                        i--;
                        cursor(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 255, 255, 255);
                    }
                }
                else if (key_check == 4) // DOWN
                {
                    if (i < 7)
                    {
                        cursorclear(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 0, 0, 0);
                        y1 += 100;
                        y2 += 100;
                        i++;
                        cursor(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 255, 255, 255);
                    }
                }
                else if (key_check == 5) //! ENTER
                {
                    cout << "HELLLO";
                    while (96)
                    {
                        if (isCursorKeyPressed(key_check))
                        {
                            system("cls");
                            if (key_check == 1) // LEFT
                            {
                                if (j > 0)
                                {
                                    swap(array[i][j - 1], array[i][j]);
                                    cursorclear(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 0, 0, 0);
                                    x1 -= 100;
                                    x2 -= 100;
                                    j--;
                                    cursor(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 255, 255, 255);
                                }
                            }
                            else if (key_check == 3) // RIGHT
                            {
                                if (j < 7)
                                {
                                    swap(array[i][j + 1], array[i][j]);
                                    cursorclear(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 0, 0, 0);
                                    x1 += 100;
                                    x2 += 100;
                                    j++;
                                    cursor(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 255, 255, 255);
                                }
                            }
                            else if (key_check == 2) // UP
                            {
                                if (i > 0)
                                {
                                    swap(array[i - 1][j], array[i][j]);
                                    cursorclear(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 0, 0, 0);
                                    y1 -= 100;
                                    y2 -= 100;
                                    i--;
                                    cursor(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 255, 255, 255);
                                }
                            }
                            else if (key_check == 4) // DOWN
                            {
                                if (i < 7)
                                {
                                    swap(array[i + 1][j], array[i][j]);
                                    cursorclear(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 0, 0, 0);
                                    y1 += 100;
                                    y2 += 100;
                                    i++;
                                    cursor(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 255, 255, 255);
                                }
                            }
                            draw_board(array);
                            cursor(x1 - 5, y1 - 5, x2 + 5, y2 + 5, 255, 255, 255);
                            break;
                        }
                    }
                }
            }
        }
        wakat--;
    }
    Sleep(22222);
    system("pause");
    return 0;
}
