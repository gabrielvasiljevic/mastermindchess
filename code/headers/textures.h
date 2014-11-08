#ifndef _TEXTURES
#define _TEXTURES

class Textures{

public:
    static sf::Texture* pawns;
    static sf::Texture* bpawns;
    static sf::Texture* towers;
    static sf::Texture* btowers;
    static sf::Texture* knights;
    static sf::Texture* bknights;
    static sf::Texture* bishops;
    static sf::Texture* bbishops;
    static sf::Texture* queens;
    static sf::Texture* bqueens;
    static sf::Texture* kings;
    static sf::Texture* bkings;
    static sf::Texture* blanks;

    static sf::Texture* bronzeMedal;
    static sf::Texture* silverMedal;
    static sf::Texture* goldMedal;
    static sf::Texture* bronzeTrophy;
    static sf::Texture* silverTrophy;
    static sf::Texture* goldTrophy;

    static sf::Texture* inputBox;
    static sf::Texture* largeInputBox;
    static sf::Texture* loginBG;
    static sf::Texture* invitationPaper;

    static sf::Texture* classicPaper;
    static sf::Texture* fischerPaper;
    static sf::Texture* capaPaper;
    static sf::Texture* chatPaper;

    static sf::Texture* water5;
    static sf::Texture* water15;
    static sf::Texture* water30;

    static sf::Texture* redMatch;
    static sf::Texture* blueMatch;
    static sf::Texture* yellowMatch;
    static sf::Texture* whiteMatch;

    static sf::Texture* classic5icon;
    static sf::Texture* classic15icon;
    static sf::Texture* classic30icon;

    static sf::Texture* fischer5icon;
    static sf::Texture* fischer15icon;
    static sf::Texture* fischer30icon;

    static sf::Texture* capa5icon;
    static sf::Texture* capa15icon;
    static sf::Texture* capa30icon;

     static sf::Texture* selectPrize(int elo){
        if(elo < 900){
            return bronzeMedal;
        }
        else if(elo < 1100){
            return bronzeMedal;
        }
        else if(elo < 1300){
            return bronzeTrophy;
        }
        else if(elo < 1500){
            return silverMedal;
        }
        else if(elo < 1700){
            return silverMedal;
        }
        else if(elo < 1900){
            return silverTrophy;
        }
        else if(elo < 2100){
            return goldMedal;
        }
        else if(elo < 2300){
            return goldMedal;
        }
        else{
            return goldTrophy;
        }
    }

    static sf::Texture* selectMatchBG(int gameType){
        switch(gameType){
            case 0:
                return blueMatch;
            break;

            case 1:
                return yellowMatch;
            break;

            case 2:
                return redMatch;
            break;

            default:
                return whiteMatch;
        }
    }

    static sf::Texture* selectPaper(int gameType){
        switch(gameType){
            case 0:
                return classicPaper;
            break;

            case 1:
                return fischerPaper;
            break;

            case 2:
                return capaPaper;
            break;

            default:
                return chatPaper;
        }
    }

    static sf::Texture* selectWaterMark(int gameTime){
        switch(gameTime){
            case 300:
                return water5;
            break;

            case 900:
                return water15;
            break;

            case 1800:
                return water30;
            break;

            default:
                return blanks;
        }
    }

    static sf::Texture* selectGameIcon(int gameMode, int gameTime){
        switch(gameMode){
            case 0:
                switch(gameTime){
                    case 300:
                        return classic5icon;
                    break;
                    case 900:
                        return classic15icon;
                    break;
                    case 1800:
                        return classic30icon;
                    break;
                }
            break;

            case 1:
                switch(gameTime){
                    case 300:
                        return fischer5icon;
                    break;
                    case 900:
                        return fischer15icon;
                    break;
                    case 1800:
                        return fischer30icon;
                    break;
                }
            break;

            case 2:
                switch(gameTime){
                    case 300:
                        return capa5icon;
                    break;
                    case 900:
                        return capa15icon;
                    break;
                    case 1800:
                        return capa30icon;
                    break;
                }
            break;

            default:
                return classic5icon;
        }
    }
};


#endif // _TEXTURES

