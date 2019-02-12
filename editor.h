#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

enum TRACKTYPE {TRAWA = 0, PROSTA = 1, SKRETP45 = 2, SKRETP90 = 3, SKRETL45 = 4, SKRETL90 = 5, PROSTAL = 6, META = 7};
enum SIINF {SITRAWA = 0, SIPROSTA = 1, SISKRETP = 2, SISKRETL = 3, SIMETA = 4};

class editor
{
    public:
        TRACKTYPE AktualnyFragment;
        int uWymiaryFragmentu[2];
        unsigned int uWymiaryTrasy[2];
        bool LoadFiles();
        bool TworzenieTrasy();
        Sprite trawa;
        Sprite prosta;
        Sprite meta;
        Sprite skretP45;
        Sprite skretP90;
        Sprite skretL45;
        Sprite skretL90;
        string strNazwaTrasy;
        Image img[8];
};

struct fragmenty
{
    int nPozycja[2];
    TRACKTYPE TypTrasy;
    char chInf;         // M - meta P - punkt kontrolny N - nic
    int nKtoryPunkt;
    SIINF inf;
    int ind;
};

bool operator<(fragmenty frag1, fragmenty frag2);
