#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "editor.h"
#include <vector>
#include <algorithm>

using namespace std;
using namespace sf;

editor editor1;

int main()
{
    editor1.LoadFiles();
    editor1.TworzenieTrasy();
    string NazwaTrasy = editor1.strNazwaTrasy;
    NazwaTrasy += ".txt";
    char ch[100];
    for (int i = 0; i < NazwaTrasy.length(); ++i)
        ch[i] = NazwaTrasy[i];
    ch[NazwaTrasy.length()] = '\0';
    cout << ch;
    editor1.strNazwaTrasy += ".png";
    fstream trasa;
    trasa.open(ch, ios::in | ios::out);
    fragmenty* FragmentyTrasy = new fragmenty[editor1.uWymiaryTrasy[0] * editor1.uWymiaryTrasy[1]];
    RenderWindow window(VideoMode(640, 480, 32), "2DRacing - map editor", Style::Close);
    const sf::Input & wejscie = window.GetInput();
    Event event;
    View& kamera = window.GetDefaultView();
    bool is = false;
    Image img;
    img.Create(editor1.uWymiaryTrasy[0] * editor1.uWymiaryFragmentu[0], editor1.uWymiaryTrasy[1] * editor1.uWymiaryFragmentu[1], Color::White);
    Sprite sprt;
    sprt.SetImage(img);
    Sprite fragment;
    int pos[2];
    const IntRect rect1 (0, 0, 150, 150);
    bool rotate;
    int indeks;
    int p[2];
    int nLiczbaZakretow = 0;
    int aktualnyPunkt = 0;
    vector<fragmenty> frag;
    while (window.IsOpened())
    {
        while(window.GetEvent(event))
        {
            if (wejscie.IsKeyDown(Key::Escape) || event.Type == Event::Closed)
            {
                img.SaveToFile(editor1.strNazwaTrasy);
                if (trasa.good())
                {
                    nLiczbaZakretow = 0;
                    for (int i = 0; i < editor1.uWymiaryTrasy[0] * editor1.uWymiaryTrasy[1]; ++i)
                    {
                        if (FragmentyTrasy[i].chInf == 'P')
                        {
                            FragmentyTrasy[i].ind = i;
                            frag.push_back(FragmentyTrasy[i]);
                            ++nLiczbaZakretow;
                        }
                    }
                    sort(frag.begin(), frag.end());
                    for (int i = 0; i < frag.size(); ++i)
                    {
                        FragmentyTrasy[frag[i].ind].nKtoryPunkt = i+1;
                    }
                    trasa << editor1.uWymiaryTrasy[0] << ' ' << editor1.uWymiaryTrasy[1] << endl;
                    trasa << editor1.uWymiaryFragmentu[0] << ' ' << editor1.uWymiaryFragmentu[1] << endl;
                    trasa << nLiczbaZakretow << endl;
                    for (int i = 0; i < editor1.uWymiaryTrasy[0] * editor1.uWymiaryTrasy[1]; ++i)
                    {
                        trasa << FragmentyTrasy[i].nPozycja[0] << ' ' << FragmentyTrasy[i].nPozycja[1] << ' ' << static_cast<int>(FragmentyTrasy[i].TypTrasy) << ' ' << FragmentyTrasy[i].chInf << ' ';
                        if (FragmentyTrasy[i].chInf == 'P')
                            trasa << FragmentyTrasy[i].nKtoryPunkt << ' ';
                        trasa << static_cast<int>(FragmentyTrasy[i].inf) << endl;
                    }
                }
                window.Close();
            }
            if (wejscie.IsMouseButtonDown(Mouse::Left))
                is = true;
            if (wejscie.IsKeyDown((Key::Num0)))
                editor1.AktualnyFragment = TRAWA;
            if (wejscie.IsKeyDown((Key::Num1)))
                editor1.AktualnyFragment = PROSTA;
            if (wejscie.IsKeyDown((Key::Num2)))
                editor1.AktualnyFragment = SKRETP45;
            if (wejscie.IsKeyDown((Key::Num3)))
                editor1.AktualnyFragment = SKRETP90;
            if (wejscie.IsKeyDown((Key::Num4)))
                editor1.AktualnyFragment = SKRETL45;
            if (wejscie.IsKeyDown((Key::Num5)))
                editor1.AktualnyFragment = SKRETL90;
            if (wejscie.IsKeyDown((Key::Num6)))
                editor1.AktualnyFragment = PROSTAL;
            if (wejscie.IsKeyDown((Key::Num7)))
                editor1.AktualnyFragment = META;
            if (wejscie.IsKeyDown(Key::W))
                kamera.Move(0, -10);
            if (wejscie.IsKeyDown(Key::S))
                kamera.Move(0, 10);
            if (wejscie.IsKeyDown(Key::A))
                kamera.Move(-10, 0);
            if (wejscie.IsKeyDown(Key::D))
                kamera.Move(10, 0);
            if (wejscie.IsKeyDown(Key::Left))
                rotate = true;
            /*if (wejscie.IsKeyDown(Key::M))
                meta = true;
            if (wejscie.IsKeyDown(Key::P))
                PunktKontrolny = true;*/
            /*if (wejscie.IsKeyDown(Key::T))
                b[0] = true;
            else if (wejscie.IsKeyDown(Key::R))
                b[2] = true;
            else if (wejscie.IsKeyDown(Key::L))
                b[3] = true;
            else
                b[1] = true;*/
        }
        if (is)
        {
            pos[0] = wejscie.GetMouseX() + kamera.GetRect().Left - (static_cast<int>(wejscie.GetMouseX() + kamera.GetRect().Left) % editor1.uWymiaryFragmentu[0]);
            pos[1] = wejscie.GetMouseY() + kamera.GetRect().Top - (static_cast<int>(wejscie.GetMouseY() + kamera.GetRect().Top) % editor1.uWymiaryFragmentu[1]);
            fragment.SetImage(editor1.img[editor1.AktualnyFragment]);
            fragment.SetPosition(pos[0], pos[1]);
            img.Copy(editor1.img[editor1.AktualnyFragment], pos[0], pos[1], rect1, true);
            sprt.SetImage(img);
            p[0] = pos[0] / editor1.uWymiaryFragmentu[0];
            p[1] = pos[1] / editor1.uWymiaryFragmentu[1];
            if (p[1] == 1)
                indeks = editor1.uWymiaryTrasy[0] + p[0];
            else if (p[1] > 1)
                indeks = (p[1] * editor1.uWymiaryTrasy[0]) + p[0];
            else
                indeks = p[0];
            FragmentyTrasy[indeks].nPozycja[0] = pos[0];
            FragmentyTrasy[indeks].nPozycja[1] = pos[1];
            FragmentyTrasy[indeks].TypTrasy = editor1.AktualnyFragment;
            if (FragmentyTrasy[indeks].TypTrasy == 2 || FragmentyTrasy[indeks].TypTrasy == 3 || FragmentyTrasy[indeks].TypTrasy == 4 || FragmentyTrasy[indeks].TypTrasy == 5)
            {
                FragmentyTrasy[indeks].chInf = 'P';
                FragmentyTrasy[indeks].nKtoryPunkt = ++aktualnyPunkt;
            }
            else if (FragmentyTrasy[indeks].TypTrasy == META)
            {
                FragmentyTrasy[indeks].chInf = 'M';
            }
            else
                FragmentyTrasy[indeks].chInf = 'N';
            is = false;

            if (FragmentyTrasy[indeks].TypTrasy == 0)
                FragmentyTrasy[indeks].inf = SITRAWA;
            else if (FragmentyTrasy[indeks].TypTrasy == 2 || FragmentyTrasy[indeks].TypTrasy == 3)
                FragmentyTrasy[indeks].inf = SISKRETP;
            else if (FragmentyTrasy[indeks].TypTrasy == 4 || FragmentyTrasy[indeks].TypTrasy == 5)
                FragmentyTrasy[indeks].inf = SISKRETL;
            else if (FragmentyTrasy[indeks].TypTrasy == 1 || FragmentyTrasy[indeks].TypTrasy == 6)
                FragmentyTrasy[indeks].inf = SIPROSTA;
            else if (FragmentyTrasy[indeks].TypTrasy == 7)
                FragmentyTrasy[indeks].inf = SIMETA;

        }
        window.Draw(sprt);
        window.Draw(fragment);
        window.Display();
        window.Clear();
    }
    return 0;
}
