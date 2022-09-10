#include <iostream>

using namespace std;

struct chessElements
{
    int pieceatxy;
    char team;
} chess[8][8];

char str[6][6] = {{' ', '1', '2', '3', '4', '5'}, {'1', 'A', 'B', 'C', 'D', 'E'}, {'2', '-', '-', '-', '-', '-'}, {'3', '-', '-', '-', '-', '-'}, {'4', '-', '-', '-', '-', '-'}, {'5', 'P', 'Q', 'R', 'S', 'T'}};

const int pawn = 6;

char ch = 'n';

class chessMethods
{
public:
    int i;
    char reply;
    void initializeboard()
    {
        int count = 1;
        for (i = 0; i < 6; i++)
        {
            chess[0][i].pieceatxy = count;
            chess[7][i].pieceatxy = count;
            chess[0][i].team = 'b';
            chess[7][i].team = 'w';
            chess[1][i].team = 'b';
            chess[6][i].team = 'w';
            chess[1][i].pieceatxy = 6;
            chess[6][i].pieceatxy = 6;

            if (i <= 3)
                count++;
            else if (i == 4)
                count -= 2;
            else
                count--;
        }
        for (int i = 2; i < 4; i++)
            for (int j = 0; j < 6; j++)
            {
                chess[i][j].pieceatxy = 0;
                chess[i][j].team = 'n';
            }
    }

    int check(int sr, int sc, int dr, int dc, char ch)
    {
        if (chess[sr][sc].pieceatxy != 0 && chess[sr][sc].team == ch)
        {
            if (chess[dr][dc].pieceatxy == 0 || chess[dr][dc].team == ((ch == 'b') ? 'w' : 'b'))
                return 1;
            else
                return 0;
        }
        else
            return 0;
    }

    int forRow(int &sr, int &sc, int &dr, int &dc)
    {
        if (dc <= sc)
        {
            for (i = sc - 1; i >= dc + 1; i--)
            {
                if (chess[sr][i].pieceatxy != 0)
                {
                    if (chess[sr][i].team == ch) // if path contains the attacking team piece
                    {
                        cout << "\nOwn Player in path\n";
                        cout << "Can't attack\n";
                        return 0;
                    }

                    else
                    {
                    label7: // if path contains opponents piece
                        cout << "Do u want to take over the piece in path(y/n):";
                        cin >> reply; // asking if want to take over the piece in path
                        if (reply == 'y' || reply == 'Y')
                        {
                            dc = i;
                            break;
                        }
                        else if (reply == 'n' || reply == 'N')
                        {
                            cout << "Wrong Path";
                            return 0;
                        }
                        else
                        {
                            cout << "\nGive answer appropriately\n";
                            goto label7;
                        }
                    }
                }
            }
        }
        else
        {
            for (i = sc + 1; i <= dc - 1; i++)
            {
                if (chess[sr][i].pieceatxy != 0)
                {
                    if (chess[sr][i].team == ch)
                    {
                        cout << "\nOwn Player in path\n";
                        cout << "Can't attack\n";
                        return 0;
                    }
                    else
                    {
                    label8:
                        cout << "Do u want to take over the piece in path(y/n):";
                        cin >> reply;
                        if (reply == 'y' || reply == 'Y')
                        {
                            dc = i;
                            break;
                        }
                        else if (reply == 'n' || reply == 'N')
                        {
                            cout << "Wrong Path";
                            return 0;
                        }
                        else
                        {
                            cout << "\nGive answer appropriately";
                            goto label8;
                        }
                    }
                }
            }
        }
        return 1;
    }

    int isMoveValid(int &sr, int &sc, int &dr, int &dc) // checks whether move is valid
    {
        switch (chess[sr][sc].pieceatxy)
        {

        case 2:
            if ((dr == sr + 2 && dc == sc + 1) || (dr == sr + 2 && dc == sc - 1) || (dr == sr - 2 && dc == sc + 1) || (dr == sr - 2 && dc == sc - 1) || (dc == sc + 2 && dr == sr + 1) || (dc == sc + 2 && dr == sr - 1) || (dc == sc - 2 && dr == sr + 1) || (dc == sc - 2 && dr == sr - 1))
                return 1;
            else
                return 0;

        case 6: // for pawn
            if (chess[sr][sc].team == 'b')
            {
                if (chess[dr][dc].team == 'w')
                    if (dr == sr + 1 && (dc == sc + 1 || dc == sc - 1))
                        return 1;
                    else
                        return 0;
                else if (sr == 1)
                {
                    if ((dr == sr + 1 || dr == sr + 2) && dc == sc)
                        return 1;
                    else
                        return 0;
                }
                else if (dr == sr + 1 && dc == sc)
                    return 1;
                else
                    return 0;
            }

            else
            {
                if (chess[dr][dc].team == 'b')
                    if (dr == sr - 1 && (dc == sc + 1 || dc == sc - 1))
                        return 1;
                    else
                        return 0;
                else if (sr == 6)
                {
                    if ((dr == sr - 1 || dr == sr - 2) && dc == sc)
                        return 1;
                    else
                        return 0;
                }
                else if (dr == sr - 1 && dc == sc)
                    return 1;
                else
                    return 0;
            }

        case 1:
            if (dr == sr)
            {
                if (forRow(sr, sc, dr, dc))
                    return 1;
                else
                    return 0;
            }

            else
                return 0;
        }
    }

    void pieceMove(int sr, int sc, int dr, int dc)
    {
        chess[dr][dc].pieceatxy = chess[sr][sc].pieceatxy;
        chess[dr][dc].team = chess[sr][sc].team;

        switch (chess[dr][dc].pieceatxy)
        {

        case 6:
            str[dr + 1][dc + 1] = ((chess[dr][dc].team == 'b') ? 'P' : 'p');
            break;
        }

        chess[sr][sc].pieceatxy = 0;
        chess[sr][sc].team = 'n';
        str[sr + 1][sc + 1] = '0';
    }

    void display()
    {
        cout << endl
             << endl;
        for (int i = 0; i < 6; i++)
        {

            for (int j = 0; j < 6; j++)
                cout << str[i][j] << "  ";
            cout << endl;
            if (i == 0)
                cout << endl;
        }
        cout << endl;
    }
};

int main()
{
    chessMethods obj;

    obj.initializeboard();

    int sr, sc, dr, dc;

    obj.display();
    int timer = 0;

    cout << "Lets START the game";

label1:

    if (timer++ % 2 == 0)
    {
        cout << "\nBLACK turn\n";
        ch = 'b';
    }
    else
    {
        cout << "\nWHITE turn\n";
        ch = 'w';
    }

    cout << "Enter source row and column:";
    cin >> sr >> sc;
    cout << "\nEnter destination row and column:";
    cin >> dr >> dc;

    cout << endl;

    if (sr >= 8 && sr <= -1 && sc >= 8 && sc <= -1 && dr >= 8 && dr <= -1 && dc >= 8 && dc <= -1 && sr == dr && sc == dc)
    {
        cout << "\nWrong Input\n";
        timer -= 1;
        goto label1;
    }
    int a, b, c, d;
    a = sr - 1;
    b = sc - 1;
    c = dr - 1;
    d = dc - 1;
    if (obj.check(a, b, c, d, ch))
    {

        if (obj.isMoveValid(a, b, c, d))
        {
            obj.pieceMove(a, b, c, d);

            obj.display();
        }
        else
        {
            cout << "\nWrong Input\n";
            timer -= 1;
            goto label1;
        }
    }
    else
    {
        cout << "\nWrong Input\n";
        timer -= 1;
        goto label1;
    }

    int flag = 0;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
            if (chess[i][j].pieceatxy == 4)
                flag++;
    }
    if (flag == 2)
        goto label1;
    else
    {
        if (ch == 'b')
            cout << "\n BLACK WINS \n";
        else
            cout << "\nWHITE WINS\n";
    }
}
