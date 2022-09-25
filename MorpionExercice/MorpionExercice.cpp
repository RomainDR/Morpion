#include <iostream>
using namespace std;

short morpionGrille[3][3] = { {0,0,0}, {0,0,0 }};
string player1, player2;
char cross = 'X', circle = '0';
bool player1Turn = true;
bool ended = false;
int attempt = 0;

/// <summary>
/// Method to check the symbol of array position (1 = X, 2 = O)
/// </summary>
/// <param name="_horizontal">position H</param>
/// <param name="_vertical">positon V</param>
/// <returns>return 'X' or 'O'</returns>
char CheckSymbol(int _horizontal, int _vertical){
    return (morpionGrille[_horizontal][_vertical] == 1 ? 'X' : morpionGrille[_horizontal][_vertical] == 2 ? 'O' : ' ');
}
/// <summary>
/// Method if the position value is available
/// </summary>
/// <param name="_value">the position value</param>
/// <returns></returns>
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
/// <summary>
/// Method for showing the grid with symbol
/// </summary>
void ShowGrid()
{
    cout << "==================================" << endl
        << "Grille" << endl
        << endl;
    string grid = "";
    for (short h = 0; h < 3; h++) {
        for (short v = 0; v < 3; v++) {
            grid = grid + " [" + CheckSymbol(h, v) + "] ";
        }
        grid += "\n";
    }
    cout << grid;
    cout << endl
        << "==================================" << endl;
}

/// <summary>
/// Check if the player win
/// </summary>
/// <param name="_player">player having played</param>
/// <returns>return true or false</returns>
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
    for (short h = 0, v = 2; h < 3; h++, v--) {
        _win += morpionGrille[h][v] == _player;
    }
    if (_win == 3) return true;
    _win = 0;
    return false;
}

/// <summary>
/// Method for insertion in array of value with symbol
/// </summary>
/// <param name="_value">case where the player played</param>
/// <param name="_symbol">the symbol of player</param>
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
        ShowGrid();
        cout << "Le joueur " << (player1Turn ? "1" : "2") << " viens de gagner" << endl;
    }
}

/// <summary>
/// Method where the differente player choose own name
/// </summary>
void ChooseName()
{
    cout << "Nom du joueur 1: ";
    cin >> player1;
    cout << "Nom du joueur 2: ";
    cin >> player2;
}

/// <summary>
/// Method of playing the game
/// </summary>
void Game()
{
    //reset the terminal 
    system("CLS");

    //showing the grid
    ShowGrid();

#pragma region player choose a case
    short _case;
    cout << "Joueur " << (player1Turn ? "1": "2") << " selectionner la case (entre 1 et 9) [Tu as " << (player1Turn ? "Le X" : "Le 0") << "]: ";
    cin >> _case;
    while (_case > 9 || _case < 1)
    {
        cout << "Valeur invalide." << endl;
        cout << "Joueur " << (player1Turn ? "1" : "2") << " selectionner la case (entre 1 et 9) [Tu as " << (player1Turn ? "Le X" : "Le 0") << "]: ";
        cin >> _case;
    }
    while (!IsValidValue(_case)) {
        cout << "La case " << _case << " est déjà remplis." << endl;
        cout << "Joueur " << (player1Turn ? "1" : "2") << " selectionner la case (entre 1 et 9) [Tu as " << (player1Turn ? "Le X" : "Le 0") << "]: ";
        cin >> _case;
    }
#pragma endregion

    //Insertion in array    
    InsertCase(_case, player1Turn ? 1 : 2);

    //attempte increment and verification if the no possibility (9 strokes possibles)
    attempt++;
    if (attempt >= 9) {
        ShowGrid();
        cout << endl << "Personne n'as gagné" << endl;
        ended = true;
    }
    //change the player turn
    player1Turn = !player1Turn;

    //reload the method for other player
    while(!ended) Game();
}

int main()
{
    ChooseName();
    Game();
}