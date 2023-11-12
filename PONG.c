#include <stdio.h>
#include <raylib.h>

#include <stdlib.h>

#define BASE 10

Rectangle racketL ,racketR ,top ,bottom ,balle,ecran; // Rectangle est un type
int xx = BASE/5 , yy = BASE/5 , scoreD = 0 , scoreG = 0 ,winner;

typedef enum EcranDeJeu { choismode ,choisdiff, Accueil, Gameplay, fin } EcranDeJeu;
typedef enum Difficulte {facile , moyen , difficile} Difficulte;
typedef enum ModeDeJeu {jcj , ordi} ModeDeJeu;
//typedef est utilis� pour cr�er un nom suppl�mentaire pour un autre type de donn�e
//enum est un type enumerer
Difficulte diff = facile;
float i = 0;
bool paused = false;
bool mute =true;








void afficherPong(void);
void InitialiserPong(void);
void RebondirBalleBord(void);
void BougerBall(void);
void RebondirBalleRaquette(void);

void afficherPong(void)
{
  SetTargetFPS(60);//fonction predefinie de la biblioteque raylib
   Texture2D pause = LoadTexture("pause.png");//permet de charger la texture de l'ecran pause


     if(paused){
                        ClearBackground(BLACK);
                        DrawTexture(pause,ecran.width/4 - 40 * BASE,ecran.height/10 - 20 * BASE,RAYWHITE);
                        //DrawTexture permet de dessiner des textures
                        DrawText("Pess SPACE to resume" , 10 * BASE, 20 * BASE , 5 * BASE , WHITE);
                        DrawText("Press ESCAPE to leave" , 10 * BASE , 30 * BASE , 5 * BASE , WHITE);
                        DrawText("Press BackSpace to go back to menu" ,10 * BASE,40 * BASE,5 * BASE,WHITE);
                        //DrawText permet d'afficher des textes a l'ecran
            }else{
                        ClearBackground(BLACK);
                        DrawRectangle(top.x , top.y , top.width ,top.height , RED);
                        DrawRectangle(racketR.x , racketR.y , racketR.width ,racketR.height , RED);
                        DrawRectangle(racketL.x , racketL.y , racketL.width ,racketL.height , RED);
                        DrawRectangle(bottom.x , bottom.y , bottom.width ,bottom.height , RED);
                        DrawRectangle(balle.x , balle.y , balle.width , balle.height , BLUE);
                        DrawRectangle(ecran.width/2 , 0 , 10 , ecran.height , RED );
                        DrawText(TextFormat("%d", scoreG), (ecran.width/2) - 45 , 5 * BASE, 6 * BASE, WHITE);
                        DrawText(TextFormat("%d", scoreD), (ecran.width/2) + 25 , 5 * BASE, 6 * BASE, WHITE);
                        //Drawrectangle permet de dessiner des rectangles
                        //DrawRectangle {position sur l'axe X ,position sur l'axe y, largeur ,longueur ,couleur}

            }

}
void InitialiserPong(void)
{    Image pause = LoadImage("pause.png");
     
    InitWindow(0 , 0 , "L'AGENCE SANITAIRE");//initialisation de la fenetre;

    ecran = (Rectangle){ecran.x , ecran.y ,GetScreenWidth()/1.25, GetScreenHeight()/1.25};
    //Nom_variable = (Rectangle){debut sur l'axe X,debut sur l'axe Y,Taille sur l'axe X,Taille sur l'axe Y}
    racketL = (Rectangle) {BASE * 1.5 , ecran.height/2 , BASE , BASE * 10};
    racketR = (Rectangle) {ecran.width - BASE * 2.5 , ecran.height/2 , BASE , BASE * 10};
    top = (Rectangle) {ecran.x , ecran.y , ecran.width , 2 * BASE};
    bottom = (Rectangle) {ecran.x , ecran.height - 20 , ecran.width, 20};
    balle = (Rectangle) {BASE * 2, BASE * 2 , BASE * 1.5, BASE * 1.5};

    SetWindowSize(ecran.width , ecran.height);//donner une taiile a la fenetre
    SetWindowPosition(ecran.width/8, ecran.height/15);//regler la position de la fenetre
    SetWindowIcon(pause);

}

void ServirBalle(void)
{
    balle.x = ecran.width/2;
    balle.y = ecran.height/2;
    //regler la position de la balle tel que balle.x represente la position sue l'axe X et balle.y represente la position sur Y

}

void BougerBalle(void){

if (!paused){

//cette instruction permet d'augmanter le score chaque balle perdante
    if (balle.x < ecran.x)
            {
                scoreD++;
                ServirBalle();
                i = 0;
            }
            else if (balle.x > ecran.width)
            {
                scoreG++;
                ServirBalle();
                i = 0;
            }
            switch (diff){
            case facile:
                {
                     balle.x += 6 * xx;
                     balle.y += yy;
                     i = i + 0.015;
                }break;
            case moyen:
                {
                     balle.x += 8 * xx;
                     balle.y += 2 *yy;
                     i = i + 0.02;
                }break;

            case difficile:
                {
                    balle.x += 12 * xx;
                     balle.y += 3 * yy;
                     i = i + 0.009;
                }
                default:break;

        //permet de changer la vitesse de la balle et le decalage de la raquette control� par l'ordi par rapport a la balle selon les difficultes du jeu
        }

    }
}
void RebondirBalleBord(void)
{

     if(CheckCollisionRecs(balle , racketR) || CheckCollisionRecs(balle , racketL)){
        xx = -xx;


//cette instruction permet de changer la direction de la balle en cas de contacte avec les raquettes
    }

   //cette instruction permet de changer la direction de la balle en cas de contacte avec le top ou le bottom

}

void RebondirBalleRaquette(void)
{
        if(CheckCollisionRecs(balle , bottom)|| CheckCollisionRecs(balle , top)){
        yy = -yy;
    
    }
}

int main()
{
ModeDeJeu mode = ordi;
EcranDeJeu  EcranActuelle = Accueil;
InitialiserPong();
 InitAudioDevice();
  Texture2D pause = LoadTexture("pause.png"); // permet de charger la texture
 Music music = LoadMusicStream("soundd.mp3");
 Sound song = LoadSound("effect.wav");
 Sound gameover = LoadSound("GameOver.wav");
  SetMusicVolume(music,1.0f);
       
PlayMusicStream(music); // permet de charger la musique de jeu
    while(!WindowShouldClose()){ // boucle principal
 UpdateMusicStream(music);
   if (IsKeyPressed(KEY_L)){
    mute = !mute;
   }
    if (mute){
        SetMusicVolume(music,1.0f);
    }else{
        SetMusicVolume(music,0.0f);
    }


            switch(EcranActuelle){
        case choismode: // permet de choisir le mode de jeu
            {
                if(IsKeyPressed(KEY_J)){ // permet de verifier si la touche J a �t� enfoncer
                    mode = jcj;
                EcranActuelle = Gameplay;} // permet de passer au gameplay
                if(IsKeyPressed(KEY_B)){
                    mode = ordi;
                    EcranActuelle = choisdiff;}// permet de passer au choix de la difficult�
                if(IsKeyPressed(KEY_BACKSPACE)){
                    EcranActuelle = Accueil;
                }
            }break;
            case choisdiff: // permet de choisir la difficult�
                {
                           if(IsKeyPressed(KEY_F)){
                        EcranActuelle = Gameplay;
                        diff = facile;}


                    if(IsKeyPressed(KEY_L)){
                        EcranActuelle = Gameplay;
                        diff = moyen;
                    }
                    if(IsKeyPressed(KEY_D)){
                        EcranActuelle = Gameplay;
                        diff = difficile;
                    }
                     if(IsKeyPressed(KEY_BACKSPACE)){
                    EcranActuelle = choismode;
                }
                }break;
                case Accueil:{
                    if(IsKeyPressed(KEY_ENTER)) {
                            EcranActuelle = choismode; // permet de passer de l'ecran d'acceuil � l'ecran de choix de mode
                       }

                }break;
                case Gameplay:
                    {
                        if (IsKeyPressed(KEY_SPACE)){
                            paused = !paused; // permet de mettre le jeu en pause ou de reprendre la partie
                        }
               if (!paused){
                    if(CheckCollisionRecs(balle , racketR) || CheckCollisionRecs(balle , racketL))
                            PlaySound(song);
                        switch (mode){
                    case ordi:
                        {
                            RebondirBalleRaquette();
                            RebondirBalleBord();
                             BougerBalle();
                             if(balle.y > top.y + top.height && balle.y + racketR.height - 20<= bottom.y - bottom.height ){
                                // la condition fait en sorte que la raquette ne depasse pas les limites du terrain
                            racketR.y = balle.y + i;
                                // permet d'ajuster la position de la raquette par rapport � la balle avec un decalage de i qui s'incremente � chaque iteration de la boucle principal


                            }

  if (IsKeyDown(KEY_A) && !CheckCollisionRecs(bottom , racketL))
                            racketL.y += 3 * BASE/2; // permet de faire monter la raquette



                        else if (IsKeyDown(KEY_Q) && !CheckCollisionRecs(top , racketL)){
                            racketL.y -= 3 * BASE/2; // permet de faire descendre la raquette
                        }
                        }break;
                    case jcj:
                        BougerBalle();
                        RebondirBalleBord();
                        RebondirBalleRaquette();
                        {
                            if (IsKeyDown(KEY_A) && !CheckCollisionRecs(bottom , racketL))
                            racketL.y += 3 *BASE/2; // permet de faire monter la raquette


                        else if (IsKeyDown(KEY_Q) && !CheckCollisionRecs(top , racketL)){
                            racketL.y -=3 * BASE/2;// permet de faire descendre la raquette
                        }
                        if (IsKeyDown(KEY_J) && !CheckCollisionRecs(bottom , racketR))
                            racketR.y +=3 * BASE/2;// permet de faire descendre la raquette


                        else if (IsKeyDown(KEY_I) && !CheckCollisionRecs(top , racketR)){
                            racketR.y -=3 * BASE/2;// permet de faire monter la raquette
                        }
                        }break;
                        default:break;

                        }
                        }
                        if(paused){
                             if(IsKeyPressed(KEY_BACKSPACE)){
                    EcranActuelle = Accueil;
                    paused = !paused;
                    scoreD = scoreG = 0;

                }
                        }




                                   if ((scoreG >= 10) || (scoreD >= 10)){

                    if (abs(scoreG - scoreD) < 2)
                        break;
                    winner = (scoreG > scoreD)? 1 : 2;// condition rapide
                    scoreD = scoreG = 0;
                    EcranActuelle = fin;
                    //arrete le jeu et reinitialise le score en cas de victoire
                    //un joueur gagne quand il atteint le score de 10 et qu'il as plus de 2 point d'ecart
                                   }

                      }
                      break;
                case fin:
                    {
                        if(IsKeyPressed(KEY_ENTER))
                            EcranActuelle = Accueil;


                    } break;
                    default: break;

            }

            BeginDrawing();

            switch (EcranActuelle){
            case choismode:
                {
                    ClearBackground(BLACK);
                    DrawText("Press J for pvp" , 5 * BASE , 5 * BASE , 5 * BASE , WHITE);
                    DrawText("Press B for pve" , 5 * BASE , 15 * BASE , 5 * BASE , WHITE);
                }break;
            case choisdiff:
                {
                    ClearBackground(BLACK);
                    DrawText("Pres F for easy" , 5 * BASE, 5 * BASE , 8 * BASE , WHITE);
                    DrawText("Press L for medium" , 5 * BASE , 15 * BASE , 8 * BASE , WHITE);
                    DrawText("Press D for hard" , 5 * BASE , 25 * BASE , 8 * BASE , WHITE);
                }break;
                case Accueil:
                    {
                        ClearBackground(BLACK);
                        DrawText("PONG", 12 * BASE, 2 * BASE, 12 * BASE, WHITE);
                        DrawText("By L'agence entertainment", 12 * BASE, 14 * BASE, 6 * BASE, WHITE);
                        DrawText("Player 1: Q, A", 12 * BASE, 39 * BASE, 2 * BASE, WHITE);
                        DrawText("Plarer 2: I, J", 12 * BASE, 420, 20, WHITE);
                        DrawText("Press ENTER to start", 12 * BASE, 45 * BASE, 2 * BASE, WHITE);
                        DrawText("Press ESCAPE to leave ", 12 * BASE, 48 * BASE, 2 * BASE, WHITE);
                        DrawText("Press SPACE to pause ", 12 * BASE, 51*BASE, 2 * BASE, WHITE);
                        DrawText("Press L to mute ", 12 * BASE, 54*BASE, 2 * BASE, WHITE);

                    }break;

                case Gameplay:
                    {
                       afficherPong();
                    }break;

                case fin:
                    {
                        ClearBackground(WHITE);
                        switch (mode){
                        case jcj:{ 

                        if(winner == 1){
                            DrawText("Player 1 WON" , 30 * BASE , 10 * BASE , 10 * BASE  , BLACK);
                            DrawText("Press ENTER to play again" , 30 * BASE  , 40 * BASE , 2 * BASE , BLACK);
                            
                        }
                        if(winner == 2){
                            DrawText("Player 2 WON" , 30 * BASE  , 10 * BASE  , 10 * BASE  , BLACK);
                           
                        }
                         DrawText("Press ENTER to play again" , 30 * BASE  , 40 * BASE , 2 * BASE , BLACK);
                          
                        }break;
                        case ordi:{
                                    if(winner == 1){
                            DrawText("YOU WON" , 30 * BASE  , 10 * BASE  , 10 * BASE  , BLACK);
                            
                                    }
                        if(winner == 2){ 
                           
                            DrawText("YOU LOST" , 30 * BASE  , 10 * BASE  , 10 * BASE  , BLACK);
                            

                        }
                        }
                         DrawText("Press ENTER to play again" , 30 * BASE  , 40 * BASE , 2 * BASE , BLACK);
                        }
                    }
                    default:break;
            




            }
            EndDrawing();

    }
    UnloadTexture(pause);// pour suprimer la musque de la ram
    UnloadMusicStream(music);
    UnloadSound(song);
    UnloadSound(gameover);
CloseAudioDevice();
CloseWindow();
    return 0;
}
