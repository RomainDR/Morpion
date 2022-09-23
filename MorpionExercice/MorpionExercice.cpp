#include <iostream>
using namespace std;

short morpionGrille[3][3] = { {0,0,0}, {0,0,0 }, {0,0,0} };
string player1, player2;
char cross = 'X', circle = '0';
bool player1Turn = true;
bool ended = false;
int attempt = 0;

char CheckSymbol(int _horizontal, int _vertical){
    return (morpionGrille[_horizontal][_vertical] == 1 ? 'X' : morpionGrille[_horizontal][_vertical] == 2 ? 'O' : ' ');
}
bool IsValidValue(short _value)
{
    short _horizontal = 0;
    short _vertical = 0;

    while (_value > 3) {
        _value -= 3;
        _horizontal++;
    }
    _vertical = _value;

    return morpionGrille[_horizontal][_vertical -1] == 0;
}
void ShowGrid()
{
    string grid = "";
    for (short h = 0; h < 3; h++) {
        for (short v = 0; v < 3; v++) {
            grid = grid + " [" + CheckSymbol(h, v) + "] ";
        }
        grid += "\n";
    }
    cout << grid;
}
void Interface()
{
    cout << "==================================" << endl
        << "Grille" << endl
        << endl;
    ShowGrid();
    cout << endl
        << "==================================" << endl;
}

bool CheckWin(short _player)
{
    int _win = 0;
    for (short h = 0; h < 3; h++) {
        for (short v = 0; v < 3; v++)
        {
            _win += (morpionGrille[h][v] == _player);
        }
        if (_win == 3) return true;
        _win = 0;
    }
    for (short v = 0; v < 3; v++) {
        for (short h = 0; h < 3; h++)
        {
            _win += morpionGrille[h][v] == _player;
        }
        if (_win == 3) return true;
        _win = 0;
    }
    for (short v = 0, h = 0; v < 3; v++, h++) {
        _win += morpionGrille[h][v] == _player;
    }
    if (_win == 3) return true;
    _win = 0;
    return false;
}
void InsertCase(short _value, short _symbol)
{
    int _horizontal = 0;
    int _vertical = 0;

    while (_value > 3) {
        _value -= 3;
        _horizontal++;
    }
    _vertical = _value;

    morpionGrille[_horizontal][_vertical - 1] = _symbol;
    if (CheckWin(player1Turn ? 1 : 2)) {
        ended = !ended;
        cout << endl << endl;
        Interface();
        cout << "Le joueur " << (player1Turn ? "1" : "2") << " viens de gagner" << endl;
    }
}
void ChooseName()
{
    cout << "Nom du joueur 1: ";
    cin >> player1;
    cout << "Nom du joueur 2: ";
    cin >> player2;
}

void Game()
{
    system("CLS");
    Interface();
    cout << attempt << endl;
    short _case;
    cout << "Joueur " << (player1Turn ? "1": "2") << " selectionner la case (entre 1 et 9) [Tu as " << (player1Turn ? "La X" : "Le rond") << "]: ";
    cin >> _case;
    while (_case > 9 || _case < 1)
    {
        cout << "Valeur invalide." << endl;
        cout << "Joueur 1, selectionner la case (entre 1 et 9): ";
        cin >> _case;
    }
    while (!IsValidValue(_case)) {
        cout << "La case " << _case << " est déjà remplis." << endl;
        cout << "Joueur 1, selectionner la case (entre 1 et 9): ";
        cin >> _case;
    }
    InsertCase(_case, player1Turn ? 1 : 2);
    attempt++;
    if (attempt > 9) {
        cout << endl << "Personne n'as gagné" << endl;
        ended = true;
    }
    player1Turn = !player1Turn;
    while(!ended) Game();
}

int main()
{
    ChooseName();
    Game();
}