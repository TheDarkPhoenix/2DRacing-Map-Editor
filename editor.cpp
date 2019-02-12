#include "editor.h"
#include <iostream>

bool editor::LoadFiles()
{
    img[0].LoadFromFile("trawa.png");
    img[1].LoadFromFile("prosta.png");
    img[2].LoadFromFile("skretL90D.png");
    img[3].LoadFromFile("skretP90.png");
    img[4].LoadFromFile("skretL90U.png");
    img[5].LoadFromFile("skretL90.png");
    img[6].LoadFromFile("prostaL.png");
    img[7].LoadFromFile("meta.png");
    trawa.SetImage(img[0]);
    skretP45.SetImage(img[1]);
    skretP90.SetImage(img[2]);
    skretL45.SetImage(img[3]);
    skretL90.SetImage(img[4]);
    prosta.SetImage(img[5]);
    meta.SetImage(img[7]);
    return true;
}

bool editor::TworzenieTrasy()
{
    editor::uWymiaryFragmentu[0] = 150;
    editor::uWymiaryFragmentu[1] = 150;
    cout << "Podaj wymiary trasy: ";
    cin >> uWymiaryTrasy[0] >> uWymiaryTrasy[1];
    cout << "Podaj nazwe trasy: ";
    cin >> strNazwaTrasy;
    AktualnyFragment = TRAWA;
    return true;
}

bool operator<(fragmenty frag1, fragmenty frag2)
{
    if (frag1.nKtoryPunkt < frag2.nKtoryPunkt)
        return true;
    else
        return false;
}
