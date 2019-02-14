#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct PlayerTable{
	char name[8];
	int pos=1;
	int color;
	int attesaTurni;
	bool inPrigione=false;
	bool end=false;
	int ntiri=0;
};

struct CaselleSpeciali{
	int pos;
	int color;
	char effetto[60];
	int attesaTurni;
	int backToPos;
};
struct ColorNames {
	char name[20];
	int contrast;
	bool alreadyTaken=false;
};


PlayerTable stats[7];
CaselleSpeciali ponte,locanda,prigione,labirinto,scheletro;
ColorNames color[16];

void PreparazioneColori();
void PreparazioneCustomizzazioniDefault();

void drawTitle();
void drawRules();

void gotoXY(int x, int y);
void setColor(int bg, int fg);
void resetColor();

void drawSettingPlayerNumber();
void drawSettingPlayerName();
void drawSettingPlayerColors();
void drawSettingAvailableColors();

void drawTabellone(int s);

void drawPonte();
void drawLocanda();
void drawPrigione();
void drawLabirinto();
void drawScheletro();

void coloraCasella(int x,int y,int n);
void saveCaselleColors();
void drawTurn();
int drawLancioDadi();

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
void showCursor(bool visible, DWORD size);

int ngioc;
int turno;
int tiro=0;
int GooseGameTitleColor;
int scelta;
bool menurepeat=false;
bool repeat=false;
int x=0,y=0;
char a=219;
char b=177;
char c=220;
char d=223;
//////////////////CARATTERI ASCII SPECIALI/////////////////////
char e=186; char m=185; char o=206; char p=204;

	        char f=201; char g=187; char j=205;  char l=203;
	        char h=200; char i=188;              char k=202;
///////////////////////////////////////////////////////////////
using namespace std;
void PreparazioneCustomizzazioniDefault(){
	/* NUMERI ASSOCIATI AI COLORI
	0   BLACK
    1   BLUE
    2   GREEN
    3   CYAN
    4   RED
    5   MAGENTA
    6   BROWN
    7   LIGHTGRAY

    8   DARKGRAY
    9   LIGHTBLUE
    10  LIGHTGREEN
    11  LIGHTCYAN
    12  LIGHTRED
    13  LIGHTMAGENTA
    14  YELLOW
    15  WHITE


      REGOLE ASSEGNAZIONE:
      POSIZIONI: -DA 2 A 62
                 -LE POSIZIONI NON DEVONO COINCIDERE
      COLORI: -DA 0 A 15

    */
    GooseGameTitleColor=14; //DETERMINA IL COLORE DELLA SCHERMATA "Goose Game" iniziale

	ponte.pos=(unsigned) 6;
	ponte.color=(unsigned) 6;
	strcpy(ponte.effetto,"ripete il movimento !");

	locanda.pos=(unsigned) 19;
	locanda.color=(unsigned) 14;
	strcpy(locanda.effetto,"rimane fermo ");
	locanda.attesaTurni=(unsigned)3;


	prigione.pos=(unsigned) 52;
	prigione.color=(unsigned) 8;
	strcpy(prigione.effetto,"rimane imprigionato affinche' un altro giocatore verra' imprigionato a sua volta !");

	labirinto.pos=(unsigned) 42;
	labirinto.color=(unsigned) 7;
	strcpy(labirinto.effetto,"torna alla casella ");
	labirinto.backToPos=(unsigned) 39;

	scheletro.pos=(unsigned) 58;
	scheletro.color=(unsigned) 12;
	strcpy(scheletro.effetto,"torna alla casella ");
	scheletro.backToPos=(unsigned) 1;
}

int main(int argc, char** argv){
	showCursor(false, 10);//Utilizza questo sottoprogramma preso da Internet che dsattiva il flash fastidioso del cursore
	srand((unsigned)time(NULL));
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);//Imposta la finestra a schermo intero
	int y=1;
	system("color 0f");
	PreparazioneColori();//Assegna ad ogni numero il suo nome testuale del colore ed il colore che fa contrasto
	PreparazioneCustomizzazioniDefault();//Definisce i parametri variabili sopra
	do{
    system("cls");
    menurepeat=false;
	drawTitle();//Disegna il titolo "Goose Game"

	////////SEQUENZA DISEGNO MENU' INIZIALE////
	setColor(0,GooseGameTitleColor);
	gotoXY(59,38);
    cout<<a;
	resetColor();
	cout<<" BENVENUTO! ";
	setColor(0,GooseGameTitleColor);
    cout<<a;
    gotoXY(51,40);
    setColor(0,GooseGameTitleColor);
    cout<<"1. Nuova Partita";
    gotoXY(51,42);
    setColor(0,7);
    cout<<"2. Carica partita";
    gotoXY(51,44);
    setColor(0,GooseGameTitleColor);
    cout<<"3. Exit";
	setColor(0,GooseGameTitleColor);
    gotoXY(51,46);
    resetColor();
    cout<<"> ";
    setColor(0,GooseGameTitleColor);
    ///////////////////////////////////////////
    cin>>scelta;
	switch(scelta){//SCELTA OPZIONE MENU'
		case 1://1. Nuova Partita

			 /////////SEQUENZA SCELTA NUMERO GIOCATORI/////////////
		 do{
		 	 scelta=0;
		     repeat=false;
		     system("cls");
	         drawTitle();
		     drawSettingPlayerNumber();
		     gotoXY(56,41);
		     cout<<"> ";
             setColor(0,GooseGameTitleColor);
             cin>>ngioc;
	        }while(ngioc<1||ngioc>6);//Ripete il ciclo finch� non viene inserito un numero valido
	        ///////////////////////////////////////////////////////
	        //////////SEQUENZA SCELTA NOMI GIOCATORI///////////////
         for(turno=1;turno<=ngioc;turno++){
		     system("cls");
	         drawTitle();
		     drawSettingPlayerName();
		     gotoXY(56,41);
		     cout<<"> ";
             setColor(0,GooseGameTitleColor);
             cin>>(stats[turno].name);
			}
			///////////////////////////////////////////////////////
			//////////SEQUENZA SCELTA COLORI GIOCATORI/////////////
		 for(turno=1;turno<=ngioc;turno++){
			 int n=0;
		     system("cls");
		     drawTitle();
		     saveCaselleColors();
		     drawSettingAvailableColors();
		     drawSettingPlayerColors();
		     gotoXY(56,41);
		     cout<<"> ";
             setColor(0,GooseGameTitleColor);
             cin>>n;
             if (n<1||n>15||color[n].alreadyTaken==true){//Se il numero messo in input NON � valido o � gi� occupato ripete il ciclo
                 turno--;
			    }
			 else{//Se il numero messo in input � valido lo imposta come colore del giocatore e lo segna come occupato
				 stats[turno].color=n;
				 color[n].alreadyTaken=true;
			    }
	        }
	        //////////////////////////////////////////////////////
	        /////////DISEGNO RULES////////////////////
	        system("cls");
	        drawRules();
	        cout<<"n\n\n\t\t";
	        system("pause");
	        //////////////////////////////////////////


	        system("cls");
            ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
            drawTabellone(1); //PRIMA APPARIZIONE DEL TABELLONE (IN INPUT HO MESSO 1: E' IL TEMPO CHE SCORRE FRA UN CARATTERE E L'ALTRO. LE PROSSIME VOLTE METTERO' 0 COSI' CHE APPAIA ISTANTANEAMENTE

	        ;
	        //////////////////INIZIO SEQUENZA PRINCIPALE GIOCO/////////////////////////////////////////////
	        for(turno=1;turno<=ngioc;turno++){ //Questo for scorre fra tutti i giocatori creando il fattore dei turni, infondo al for c'� il controllo che permette di ritornare a turno=1, nel caso sia turno==ngioc
	         if(stats[turno].attesaTurni!=0||stats[turno].inPrigione==true){ //Se il giocatore � sotto l'effetto di una casella speciale, lascia il compito al void drawTurn() che disegner� l'effetto della casella sullo schermo
	         	 drawTurn(); //Stampa "'nome giocatore' tocca a te!" e nel caso il giocatore sia sotto l'effetto di una casella speciale, l'effetto
			 }
	         else if(stats[turno].end==false&&stats[turno].attesaTurni==0&&stats[turno].inPrigione==false){//Se il giocatore � libero da vincoli, fa partire il tutto
	         	 int retrocessione,avanzamento; //Variabili per creare l'effetto della retrocessione nel caso che si arrivi alla casella 63 e che il tiro di dadi non sia esatto
			     drawTurn(); //Stampa "'nome giocatore' tocca a te!"
			     gotoXY(160,10); setColor(stats[turno].color,color[stats[turno].color].contrast);//Imposta lo sfondo dei caratteri del colore del giocatore ed il testo del colore che fa contrasto

				 cout<<"Premi un tasto per lanciare i dadi!";//Il messaggio del system("pause") <<leggere sotto>>
			   	 system("pause >nul")/*Crea un system("pause") senza il messaggio*/;resetColor();gotoXY(160,10);cout<<"                                   ";//Quando il giocatore va avanti, cancella il messaggio del system("pause")

				 stats[turno].ntiri++;//Incrementa i tiri del giocatore cos� da stilare una classifica a fine programma
				 tiro=drawLancioDadi();//Fa partire il sottoprogramma che stampa l'animazione degli slot e returna la somma dei dadi

                 //////////////////////
                 /////////SEQUENZA ANIMAZIONE SPOSTAMENTO PEDINA///////
                 avanzamento=tiro;//Di default avanzamento � uguale al tiro di dadi
                 retrocessione=0;
                 if((stats[turno].pos)+tiro>63){//Se il tiro di dadi non � esatto, fa le differenze e quindi retrocessione sar� uguale
                 	 retrocessione=(stats[turno].pos)+tiro-63;
                 	 avanzamento=tiro-retrocessione;
				    }
                 for(int i=0;i<avanzamento;i++){//Avanza di 'avanzamento' caselle
               	     stats[turno].pos++;
               	     Sleep(150);
               	     drawTabellone(0);
			        }
			     for(int i=0;i<retrocessione;i++){//Retrocede di 'retrocessione' caselle, che di default � 0
               	     stats[turno].pos--;
               	     Sleep(150);
               	     drawTabellone(0);
			        }
			    /////////////////////////////////////////////////////////////////////
			    /////////////CONTROLLO CASELLE SPECIALI//////////////////////////////
			     if(stats[turno].pos==ponte.pos){//Ponte
			         Sleep(500);
			     	 drawPonte();//Disegna l'icona del ponte

                     ///Disegna frase con nome del giocatore del suo colore, effetto e variabili
                     setColor(ponte.color,color[ponte.color].contrast); cout<<"Ponte!  ";
			     	 setColor(stats[turno].color,color[stats[turno].color].contrast); cout<<stats[turno].name;
			     	 setColor(ponte.color,color[ponte.color].contrast); cout<<" , "<<ponte.effetto;

			     	 ///////////Ripete il movimento////////
			     	 avanzamento=tiro; //Di default avanzamento � uguale al tiro di dadi
                     retrocessione=0;
                     if((stats[turno].pos)+tiro>63){
                 	     retrocessione=(stats[turno].pos)+tiro-63;
                 	     avanzamento=tiro-retrocessione;
				        }
                     for(int i=0;i<avanzamento;i++){//Avanza di 'avanzamento' caselle
               	         stats[turno].pos++;
               	         Sleep(90);
               	         drawTabellone(0);
			            }
			         for(int i=0;i<retrocessione;i++){//Retrocede di 'retrocessione' caselle, che di default � 0
               	         stats[turno].pos--;
               	         Sleep(90);
               	         drawTabellone(0);
			            }

			         Sleep(3000);
				    }
				 if(stats[turno].pos==locanda.pos){//Locanda
				 	 Sleep(500);
			     	 drawLocanda();//Disegna l'icona della locanda

			     	 ///Disegna frase con nome del giocatore del suo colore, effetto e variabili
			     	 setColor(locanda.color,color[locanda.color].contrast); cout<<"Locanda!  ";
			     	 setColor(stats[turno].color,color[stats[turno].color].contrast); cout<<stats[turno].name;
					 setColor(locanda.color,color[locanda.color].contrast); cout<<" "<<locanda.effetto<<" per "<<locanda.attesaTurni<<" turni !";

			     	 stats[turno].attesaTurni=locanda.attesaTurni;//Imposta l'attesa dei turni del giocatore con quello della casella (cambiabile in cima al .cpp)
			     	 Sleep(3000);
				    }
			     if(stats[turno].pos==prigione.pos){//Prigione
			     	 Sleep(500);
			     	 drawPrigione();//Disegna l'icona della prigione

			     	 bool exit=false;
			     	 for(int n=1;n<=ngioc&&exit==false;n++){
			     	 	 if(stats[n].inPrigione==true){//Se un'altro giocatore era in prigione, lo libera e stampa il testo di liberazione di conseguenza

			     	 	 	 setColor(stats[n].color,color[stats[n].color].contrast); cout<<stats[n].name;
			     	 	 	 setColor(prigione.color,color[prigione.color].contrast); cout<<" e' stato liberato da ";
			     	 	 	 setColor(stats[turno].color,color[stats[turno].color].contrast); cout<<stats[turno].name;

			     	 	 	 stats[n].inPrigione=false;stats[turno].inPrigione=true;
			     	 	 	 exit=true;
						    }
						 else if(n==ngioc){//... altrimenti lo imprigiona e stampa il testo di imprigionamento

						   	 setColor(prigione.color,color[prigione.color].contrast); cout<<"Prigione!  ";
			     	         setColor(stats[turno].color,color[stats[turno].color].contrast); cout<<stats[turno].name;
					         setColor(prigione.color,color[prigione.color].contrast); cout<<" "<<prigione.effetto;

					         stats[turno].inPrigione=true;
						    }
					    }



			     	 Sleep(3000);
			     	 resetColor();
				    }
				 if(stats[turno].pos==labirinto.pos){//Labirinto
			     	 Sleep(500);
					 drawLabirinto();//Disegna l'icona del labirinto

					 ///Disegna frase con nome del giocatore del suo colore, effetto e variabili
			     	 setColor(labirinto.color,color[labirinto.color].contrast); cout<<"Labirinto!  ";
			     	 setColor(stats[turno].color,color[stats[turno].color].contrast); cout<<stats[turno].name;
			     	 setColor(labirinto.color,color[labirinto.color].contrast); cout<<" , "<<labirinto.effetto<<labirinto.backToPos;

			     	 for(stats[turno].pos; stats[turno].pos<labirinto.backToPos; stats[turno].pos++){
               	         stats[turno].pos++;
               	         Sleep(90);
               	         drawTabellone(0);
			            }
			         for(stats[turno].pos; stats[turno].pos>labirinto.backToPos; stats[turno].pos--){
               	         stats[turno].pos--;
               	         Sleep(90);
               	         drawTabellone(0);
			            }
			         Sleep(3000);
				    }
				 if(stats[turno].pos==scheletro.pos){//Scheletro
			     	 Sleep(500);
					 drawScheletro();//Disegna l'icona dello scheletro

					 ///Disegna frase con nome del giocatore del suo colore, effetto e variabili
			     	 setColor(scheletro.color,color[scheletro.color].contrast); cout<<"Scheletro!  ";
			     	 setColor(stats[turno].color,color[stats[turno].color].contrast); cout<<stats[turno].name;
			     	 setColor(scheletro.color,color[scheletro.color].contrast); cout<<" , "<<scheletro.effetto<<scheletro.backToPos;

			     	 for(stats[turno].pos; stats[turno].pos<scheletro.backToPos; stats[turno].pos++){
               	         stats[turno].pos++;
               	         Sleep(90);
               	         drawTabellone(0);
			            }
			         for(stats[turno].pos; stats[turno].pos>scheletro.backToPos; stats[turno].pos--){
               	         stats[turno].pos--;
               	         Sleep(90);
               	         drawTabellone(0);
			            }
			         Sleep(3000);
				    }
			     //////////////////////////////////////////////////////////////////////////////////////
			     //////////////////////////////////////////////////////////////////////////////////////
			     if(stats[turno].pos==63){
			   	     stats[turno].end=true;
			        }

			    }
				gotoXY(149,34);
			    system("pause");


			     if(turno==ngioc){
			   	     turno=0;
			        }
			}
	        //////////////////FINE SEQUENZA PRINCIPALE GIOCO/////////////////////////////////////////////








































			break;



		case 2://2. Carica Partita
			menurepeat=true;

			break;

		case 3://3. Esci
			system("cls");
			drawTitle();
			setColor(0,GooseGameTitleColor);
	        gotoXY(59,38);
            cout<<a;
	        resetColor();
	        cout<<" TE NE VAI DI GIA'? TORNA PRESTO! ";
	        setColor(0,GooseGameTitleColor);
            cout<<a;
            resetColor();
	        cout<<"\n\n\n\t\t\t\t\t\t\t";
			break;
		default://Opzione inesistente
			gotoXY(49,46);
			cout<<" ";
			gotoXY(49,46);
			menurepeat=true;//Fa in modo che il men� si ripeta
			break;
	}
	}while (menurepeat==true);//Se � su true(� stato digitato un comando non valido) ripete il men�

	cout<<"\n\n\n";
	int test;
	cin>>test;

	return 0 ;
}

void PreparazioneColori(){/*QUA' ASSEGNA AD OGNI NUMERO DI COLORE UNA STRINGA + IL NUMERO DEL COLORE CHE FA CONTRASTO + BOOL=FALSE CHE DESCRIVE SE IL COLORE E' GIA STATO USATO (DI BASE E' FALSE)
                                    UTILE PER IL PRGRAMMA PI� AVANTI*/
	strcpy(color[0].name,"Nero");
	strcpy(color[1].name,"Blu");
	strcpy(color[2].name,"Verde");
	strcpy(color[3].name,"Ciano");
	strcpy(color[4].name,"Rosso");
	strcpy(color[5].name,"Magenta");
	strcpy(color[6].name,"Marrone");
	strcpy(color[7].name,"Grigio Chiaro");
	strcpy(color[8].name,"Grigio Scuro");
	strcpy(color[9].name,"Blu Chiaro");
	strcpy(color[10].name,"Verde Chiaro");
	strcpy(color[11].name,"Ciano Chiaro");
	strcpy(color[12].name,"Rosso chiaro");
	strcpy(color[13].name,"Magenta Chiaro");
	strcpy(color[14].name,"Giallo Chiaro");
	strcpy(color[15].name,"Bianco");
	color[0].contrast=15;
	color[1].contrast=15;
	color[2].contrast=0;
	color[3].contrast=15;
	color[4].contrast=0;
	color[5].contrast=0;
	color[6].contrast=15;
	color[7].contrast=0;
	color[8].contrast=15;
	color[9].contrast=15;
	color[10].contrast=0;
	color[11].contrast=0;
	color[12].contrast=0;
	color[13].contrast=0;
	color[14].contrast=0;
	color[15].contrast=0;

	color[0].alreadyTaken=false;
	color[1].alreadyTaken=false;
	color[2].alreadyTaken=false;
	color[3].alreadyTaken=false;
	color[4].alreadyTaken=false;
	color[5].alreadyTaken=false;
	color[6].alreadyTaken=false;
	color[7].alreadyTaken=false;
	color[8].alreadyTaken=false;
	color[9].alreadyTaken=false;
	color[10].alreadyTaken=false;
	color[11].alreadyTaken=false;
	color[12].alreadyTaken=false;
	color[13].alreadyTaken=false;
	color[14].alreadyTaken=false;
	color[15].alreadyTaken=false;
}

void drawTitle(){//DISEGNA IL TITOLO "Goose Game"
	setColor(0 , GooseGameTitleColor);
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a;
	cout<<"\n\t\t"<<" "<<a<<a<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<a<<b<<b<<b<<b<<a;
	cout<<"\n\t\t"<<a<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a;
	cout<<"\n\t\t"<<a<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<" "<<" "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<" "<<" "<<" "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a;
	cout<<"\n\t\t"<<a<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<" "<<" "<<a<<b<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<b<<b<<b<<b<<b<<a<<a;
	cout<<"\n\t\t"<<a<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<a<<a<<a<<a<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<a;
	cout<<"\n\t\t"<<a<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<" "<<a<<b<<b<<b<<b<<b<<a<<" "<<" "<<a<<a<<a<<a<<a<<a <<a<<b<<b<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<b<<b<<b<<b<<b<<b<<a;
	cout<<"\n\t\t"<<a<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a;
	cout<<"\n\t\t"<<a<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a;
	cout<<"\n\t\t"<<" "<<a<<a<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<a <<a<<b<<b<<b<<b<<b<<b<<b<<a;
	cout<<"\n\t\t"<<" "<<" "<<a<<a<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<a<<a<<a<<a<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<" "<<" "<<a<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<b<<b<<b<<b<<b<<b<<a<<a<<a<<b<<b<<b<<a<<" "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<" "<<" "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<" "<<" "<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<a<<a<<a<<a<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a;
	cout<<"\n\t\t";
	cout<<"\n\t\t";
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<a<<b<<b<<b<<b<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<a<<" "<<" "<<a<<b<<b<<b<<b<<b<<b<<b<<a<<a<<" "<<" "<<" "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<b<<b<<b<<b<<b<<a<<" "<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<" "<<a<<b<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<b<<b<<b<<b<<b<<a<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<" "<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<b<<b<<b<<b<<b<<a<<" "<<a<<b<<b<<b<<b<<b<<a<<a<<a<<b<<b<<b<<b<<b<<b<<a<<a<<a<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<b<<b<<b<<b<<b<<b<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<b<<b<<b<<b<<a<<" "<<" "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<" "<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<" "<<a<<b<<b<<b<<b<<a<<a<<a<<a<<b<<b<<b<<b<<b<<b<<a<<" "<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<a<<" "<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<b<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<a<<b<<b<<b<<b<<a<<a<<a<<b<<b<<b<<a<<" "<<" "<<" "<<" "<<a<<b<<b<<b<<b<<b<<a<<" "<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<a<<a<<a<<a<<b<<b<<b<<b<<b<<b<<a<<" "<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<" "<<a<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<b<<b<<b<<b<<b<<b<<a<<a<<a<<b<<b<<b<<a<<" "<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<a<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<" "<<" "<<" "<<a<<b<<b<<b<<b<<a<<" "<<" "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a;
	cout<<"\n\t\t"<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<a<<a<<a<<a<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a;
    resetColor();
}
void drawRules(){/*DISEGNA LE REGOLE. SICCOME IL PROGRAMMA � MODULARE UTILIZZA LE VARIABILI PER DECIDERE:
                              -Colore dell'evidenziatore -Testo dell'effetto -Numero dei turni da aspettare/dela casella a cui retrocedere*/
 	setColor(0 , GooseGameTitleColor);
	cout<<"\n\n\n\t\t\t\t"<<" "<<" "<<" "<<c<<a<<a<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<" "<<c<<a<<a<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<" "<<c<<a<<a<<a<<a<<a<<a<<c<<" "<<" "<<" "<<c<<a<<a<<a<<a<<a<<a<<c<<" "<<" "<<" "<<c<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<c<<a<<a<<a<<a<<a<<a<<a<<a;
	cout<<"\n\t\t\t\t"<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a;
	cout<<"\n\t\t\t\t"<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<d<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<d<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<d;
	cout<<"\n\t\t\t\t"<<" "<<c<<a<<a<<a<<c<<c<<c<<c<<a<<a<<d<<" "<<" "<<c<<a<<a<<a<<c<<c<<c<<" "<<" "<<" "<<" "<<" "<<" "<<c<<a<<a<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<c<<a<<a<<a<<c<<c<<c;
	cout<<"\n\t\t\t\t"<<d<<d<<a<<a<<a<<d<<d<<d<<d<<d<<" "<<" "<<" "<<d<<d<<a<<a<<a<<d<<d<<d<<" "<<" "<<" "<<" "<<" "<<d<<d<<a<<a<<a<<" "<<a<<a<<a<<a<<c<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<d<<d<<a<<a<<a<<d<<d<<d;
	cout<<"\n\t\t\t\t"<<d<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<c<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<c;
	cout<<"\n\t\t\t\t"<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<a<<a<<a<<a<<" "<<" "<<" "<<" "<<c<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a;
	cout<<"\n\t\t\t\t"<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<d<<" "<<" "<<" "<<d<<a<<a<<a<<a<<a<<a<<d<<" "<<" "<<a<<a<<a<<a<<a<<c<<c<<a<<a<<" "<<" "<<" "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a;
	cout<<"\n\t\t\t\t"<<" "<<" "<<a<<a<<a<<" "<<" "<<" "<<" "<<a<<a<<a                                      <<d;

	gotoXY(26,15);
	setColor(0,GooseGameTitleColor);
	cout<<"- ";
	resetColor();
    cout<<"Ci sono 63 caselle, colui che raggiunge la 63esima con il minor numero di tiri vince! ";
    gotoXY(31,16);
    cout<<"(il tiro di dadi deve essere esatto, altrimenti si retrocede per la differenza)";
	gotoXY(26,18);
	setColor(0,GooseGameTitleColor);
	cout<<"- ";
	resetColor();
    cout<<"Le caselle speciali hanno vari effetti come:";
    gotoXY(33,20);
    setColor(ponte.color,color[ponte.color].contrast);
    cout<<"Ponte : "<<ponte.effetto;

    gotoXY(33,22);
    setColor(locanda.color,color[locanda.color].contrast);
    cout<<"Locanda : "<<locanda.effetto<<"per "<<locanda.attesaTurni<<" turni !";

    gotoXY(33,24);
    setColor(prigione.color,color[prigione.color].contrast);
    cout<<"Prigione : "<<prigione.effetto;

    gotoXY(33,26);
    setColor(labirinto.color,color[prigione.color].contrast);
    cout<<"Labirinto : "<<labirinto.effetto<<labirinto.backToPos<<" !";

    gotoXY(33,28);
    setColor(scheletro.color,color[scheletro.color].contrast);
    cout<<"Scheletro : "<<scheletro.effetto<<scheletro.backToPos<<" !\n";
    resetColor();
}
void saveCaselleColors(){//IMPOSTA I COLORI USATI DALLE CASELLE SPECIALI alreadyTaken=true COS� DA BARRARE I COLORI DI ROSSO E PER NON POTER PERMETTERE AI GIOCATORI DI SCEGLIERLI

	color[ponte.color].alreadyTaken=true;
	color[locanda.color].alreadyTaken=true;
	color[prigione.color].alreadyTaken=true;
	color[labirinto.color].alreadyTaken=true;
	color[scheletro.color].alreadyTaken=true;
}

void gotoXY(int x, int y) {//FUNZIONE PER SPOSTARE IL CURSORE NELLA FINESTRA. Grazie Caramelli :>
        COORD CursorPos = {x, y};
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hConsole, CursorPos);
}

void setColor(int bg, int fg) {//IMPOSTA IL COLORE DEL TESTO (SFONDO E TESTO)
    int val;
    if (bg<0) bg=0;
    if (fg>15) fg=15;
    val=bg*16+fg;
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        val);
}

void resetColor(){//RESETTA IL TESTO RIPORTANDOLO A BIANCO SU SFONDO NERO
	setColor(0,15);
}

void drawSettingPlayerNumber(){//DISEGNA LA DOMANDA SUL NUMERO DI GIOCATORI
	 setColor(0,GooseGameTitleColor);
	 gotoXY(59,38);
     cout<<a;
	 resetColor();
	 cout<<" QUANTI GIOCATORI SIETE? (1 - 6) ";
	 setColor(0,GooseGameTitleColor);
     cout<<a;
	 resetColor();
}

void drawSettingPlayerName(){//DISEGNA LA DOMANDA SUL NOME DEI GIOCATORI
	 setColor(0,GooseGameTitleColor);
	 gotoXY(59,38);
     cout<<a;
	 resetColor();
	 cout<<" GIOCATORE "<<turno<<", come ti chiami? ";
	 setColor(0,GooseGameTitleColor);
     cout<<a;
	 resetColor();
	 gotoXY(73,39);
	 cout<<"(max 5 lettere)";
}

void drawSettingAvailableColors(){//DISEGNA I COLORI DISPONIBILI A SX DELLA FINESTRA
	int y;
	int ncolor;
	for(int ncolors=1,y=29;ncolor<15;ncolor++,y+=2){//Ciclo che esamina tutti i colori e incrementa la y per il GotoXY cos� da mettere in colonna i colori
	    gotoXY(4,y);

		if(color[ncolor].alreadyTaken==true){//Se il colore � gi� stato preso lo stampa barrato di rosso
		 setColor(4,15);
		 cout<<a<<a<<" "<<ncolor<<" = "<<color[ncolor].name;
		}

		else{ //Se il colore NON � gi� stato preso lo stampa del suo colore
		 setColor(0,ncolor);
		 cout<<a<<a<<" "<<ncolor<<" = "<<color[ncolor].name;
		}
	}
	resetColor();
}
	void drawSettingPlayerColors(){//DISEGNA LA DOMANDA SUL COLORE DEI GIOCATORI
	 setColor(0,GooseGameTitleColor);
	 gotoXY(59,38);
     cout<<a;
	 resetColor();
	 cout<<" "<<stats[turno].name<<", che colore vuoi dare al tuo personaggio? ";
	 setColor(0,GooseGameTitleColor);
     cout<<a;
	 resetColor();
    }
    void drawTurn(){
     //////////CANCELLAZIONE AREA PERSONALIZZATA GIOCATORE//////
     resetColor();
     for(int y=2,x=133;y<71;y++){
         gotoXY(x,y);
    	 for(int x=133;x<253;x++){
    		 cout<<" ";
			}
		}
	 ////////////////////////////////////////////////////////////

     if(stats[turno].attesaTurni!=0){
     	 stats[turno].attesaTurni--;
     	 drawLocanda();
     	 setColor(stats[turno].color,color[stats[turno].color].contrast); cout<<stats[turno].name;
     	 setColor(locanda.color,color[locanda.color].contrast); cout<<" � intento a bere una bella birra fresca! Deve aspettare ancora "<<stats[turno].attesaTurni<<" turni!";
		}
     else if(stats[turno].inPrigione==true){
     	 drawPrigione();
     	 setColor(stats[turno].color,color[stats[turno].color].contrast); cout<<stats[turno].name;
     	 setColor(prigione.color,color[prigione.color].contrast); cout<<" e' imprigionato! Qualcuno vada a salvarlo!!";
		}
	 else{
	 	 gotoXY(160,8);
         setColor(stats[turno].color,color[stats[turno].color].contrast);
         cout<<stats[turno].name<<" , TOCCA A TE!";
		}
	}
	int drawLancioDadi(){//Disegna l'animazione e returna come risultato il risultato del lancio dei dadi
	                      //Le x e le y sono le coordinate del'angolo in alto a sx della casella di sinistra. Da l� engono disegnati tutti e due gli slot
         gotoXY(160,9);
		 setColor(stats[turno].color,color[stats[turno].color].contrast);
         cout<<"Tiri effettuati: "<<stats[turno].ntiri;
		 /////////////DISEGNO CASELLE LANCIO DADI///////////////////////////
         for(int x=154,y=12,n=1;n<=2;x+=8,n++){
         	 setColor(stats[turno].color,color[stats[turno].color].contrast);

         	 gotoXY(x+1,y); for(int i=1;i<=7;i++){ cout<<j; }//Disegna il lato superiore
             gotoXY(x+1,y+6); for(int i=1;i<=7;i++){ cout<<j; }//Disegna il lato inferiore
		     for(int i=0;i<=4;i++){  gotoXY(x,y+1+i); cout<<e; }//Disegna il lato sx
		     for(int i=0;i<=4;i++){  gotoXY(x+8,y+1+i); cout<<e; }//Disegna il lato dx

		     switch(n){//INSERIMENTO CARATTERI CHE FANNO "DA ANGOLO"
		     	 case 1://Primo slot
		     	 	 gotoXY(x,y); cout<<f;//Angolo in alto a sx
            	     gotoXY(x,y+6); cout<<h;//Angolo in basso a sx
            	     gotoXY(x+8,y); cout<<l;//Angolo in alto a dx
            	     gotoXY(x+8,y+6); cout<<k;//Angolo in basso a dx
		     	 break;
		     	 case 2://Secondo slot
		     		 gotoXY(x,y); cout<<l;//Angolo in alto a sx
            	     gotoXY(x,y+6); cout<<k;//Angolo in basso a sx
            	     gotoXY(x+8,y); cout<<g;//Angolo in alto a dx
            	     gotoXY(x+8,y+6); cout<<i;//Angolo in basso a dx
		     	 break;
			    }
		    }
    	 /////////////////////////////////////////////////////////////////

    	 int num1a=3,num1b=2,num1c=1;//Variabili dei 3 numeri che scorrono nel primo slot. Il numero risultante a fine animazione � quello centrale (num1b)
    	 int num2a=3,num2b=2,num2c=1;//Variabili dei 3 numeri che scorrono nel secondo slot. Il numero risultante a fine animazione � quello centrale (num2b)
    	 int time; //E' la velocit� con cui i numeri scorrono nello slot. Incrementandolo volta per volta si ha l'effetto dei numeri che rallentano
    	 int k1,k2;//Variabile temporale per poter trasferire il contenuto da una variabile all'altra
		 for(time=5;time<300;time+=20){
		 	 ///Qua genera il numero in basso del PRIMO slot e scorre il resto dei numeri presenti del PRIMO slot in alto
    	 	 Sleep(time);
    	 	 k1=num1c;
    	 	 num1c=rand()%6+1;
    	 	 k2=num1b;
    	 	 num1b=k1;
    	 	 num1a=k2;
    	 	 ///////////////

    	 	 ///Qua genera il numero in basso del SECONDO slot e scorre il resto dei numeri presenti del SECONDO slot in alto
    	 	 Sleep(time);
    	 	 k1=num1c;
    	 	 num2c=rand()%6+1;
    	 	 k2=num1b;
    	 	 num2b=k1;
    	 	 num2a=k2;
    	 	 ///////////////

    	 	 setColor(stats[turno].color,color[stats[turno].color].contrast);
    	 	 /////Stampa numeri PRIMO slot////
    	 	 x=158,y=17;//Coordinate numero infondo al PRIMO slot
    	 	 gotoXY(x,y);cout<<num1c;
    	 	 gotoXY(x,y-2);cout<<num1b;
    	 	 gotoXY(x,y-4);cout<<num1a;
    	 	 /////////////////////////////////

    	 	 /////Stampa numeri SECONDO slot////
    	 	 x=166,y=17;//Coordinate numero infondo al SECONDO slot
    	 	 gotoXY(x,y);cout<<num2c;
    	 	 gotoXY(x,y-2);cout<<num2b;
    	 	 gotoXY(x,y-4);cout<<num2a;
    	 	 /////////////////////////////////

		 }

             /////PULIZIA NUMERI NELLA SLOT ECCETTO PER QUELLI CENTRALI//
    	 	 x=158,y=17;
    	 	 resetColor();
    	 	 gotoXY(x,y);cout<<" ";
    	 	 gotoXY(x,y-4);cout<<" ";
    	 	 x=166,y=17;
    	 	 gotoXY(x,y);cout<<" ";;
    	 	 gotoXY(x,y-4);cout<<" ";
    	 	 ///////////////////////////////////////////////////////////
			 gotoXY(160,19);cout<<"Hai fatto "<<num1b+num2b<<" !"; //Stampa il testo con il risultato

     return num1b+num2b;//returna la somma dei 2 numeri centrali dei due 'slot' (aka 'dadi')
	}

	void showCursor(bool visible, DWORD size){//SOTTOPROGRAMMA PRESO SU INTERNET CHE ATTIVA/DISATTIVA IL FLASH FASTIDIOSO DEL CURSORE
	                            // set bool visible = 0 - invisible, bool visible = 1 - visible
	 if(size == 0){
		 size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
	    }
	 CONSOLE_CURSOR_INFO lpCursor;
	 lpCursor.bVisible = visible;
	 lpCursor.dwSize = size;
	 SetConsoleCursorInfo(console,&lpCursor);
    }

    void drawTabellone(int s){/*DISEGNA IL TABELLONE UTILIZZANDO PER OGNI SEGMENTO 1 FOR
                                -Per semplicit� descriver� solo il primo for visto che quelli dopo sono analoghi
								 Partiamo col dire che le x e y si riferiscono alla posizione del numerino, tutto ci� che viene stampato prende come riferimento la posizione della x e della y

	        char e=186; char m=185; char o=206; char p=204;

	        char f=201; char g=187; char j=205;  char l=203;
	        char h=200; char i=188;              char k=202;
	        */
    	int y; int x;//Dichiarazione di x e y
        for(int n=1,y=3,x=8;n<=13;n++,x+=10){//Questo for() stampa tutto il primo pezzo orizzontale del tabellone (e quindi da una casella all'altra incrementa la x)
             resetColor();
             setColor(GooseGameTitleColor,color[GooseGameTitleColor].contrast);//Imposta il colore dei contorni del tabellone

             //////////////////DISEGNO DELLA CASELLA////////////////////

             gotoXY(x-6,y-1); for(int i=1;i<=9;i++){ cout<<j; Sleep(s); }//Disegna il lato superiore
             gotoXY(x-6,y+6); for(int i=1;i<=9;i++){ cout<<j; Sleep(s); }//Disegna il lato inferiore
			 for(int i=0;i<=6;i++){  gotoXY(x-7,y+i); cout<<e; Sleep(s); }//Disegna il lato sx
			 for(int i=0;i<=6;i++){  gotoXY(x+3,y+i); cout<<e; Sleep(s); }//Disegna il lato dx

			 switch(n){//INSERIMENTO CARATTERI CHE FANNO "DA ANGOLO"
            	 case 1://Casella 1
            	     gotoXY(x-7,y-1); cout<<f;//Angolo in alto a sx
            	     gotoXY(x-7,y+6); cout<<h;//Angolo in basso a sx
            	     gotoXY(x+3,y-1); cout<<l;//Angolo in alto a dx
            	     gotoXY(x+3,y+6); cout<<k;//Angolo in basso a dx
            	     break;
            	 case 13://Casella 13
            	     gotoXY(x-7,y-1); cout<<l;
            	     gotoXY(x-7,y+6); cout<<k;
					 gotoXY(x+3,y-1); cout<<g;
            	     gotoXY(x+3,y+6); cout<<m;
            	     break;
                 default://Il resto delle caselle di questa riga
                 	 gotoXY(x-7,y-1); cout<<l;
                 	 gotoXY(x-7,y+6); cout<<k;
            	     gotoXY(x+3,y-1); cout<<l;
					 gotoXY(x+3,y+6); cout<<k;
            	     break;
				}
			 coloraCasella(x,y,n);//Riempie la casella del suo colore (nel caso sia una casella speciale) e dei nomi dei giocatori
           }

        for(int n=14,y=10,x=128;n<=22;n++,y+=7){
             resetColor();

             setColor(GooseGameTitleColor,color[GooseGameTitleColor].contrast);
             gotoXY(x-6,y-1); for(int i=1;i<=9;i++){ cout<<j;Sleep(s); }
             gotoXY(x-6,y+6); for(int i=1;i<=9;i++){ cout<<j;Sleep(s); }
			 for(int i=0;i<=6;i++){  gotoXY(x-7,y+i); cout<<e; Sleep(s); }
			 for(int i=0;i<=6;i++){  gotoXY(x+3,y+i); cout<<e; Sleep(s); }

			 switch(n){
            	 case 14:
            	     gotoXY(x-7,y-1); cout<<o;
            	     gotoXY(x-7,y+6); cout<<k;
            	     gotoXY(x+3,y-1); cout<<m;
            	     gotoXY(x+3,y+6); cout<<m;
            	     break;
            	 case 22:
            	 	 gotoXY(x-7,y-1); cout<<o;
            	 	 gotoXY(x-7,y+6); cout<<k;
            	     gotoXY(x+3,y-1); cout<<m;
            	     gotoXY(x+3,y+6); cout<<i;
            	     break;
                 default:
            	     gotoXY(x-7,y-1); cout<<p;
					 gotoXY(x-7,y+6); cout<<p;
            	     gotoXY(x+3,y-1); cout<<m;
            	     gotoXY(x+3,y+6); cout<<m;
            	     break;
				}
			 coloraCasella(x,y,n);
           }
        for(int n=23,y=66,x=118;n<=32;n++,x-=10){
             resetColor();

             setColor(GooseGameTitleColor,color[GooseGameTitleColor].contrast);
             gotoXY(x-6,y-1); for(int i=1;i<=9;i++){ cout<<j;Sleep(s); }
             gotoXY(x-6,y+6); for(int i=1;i<=9;i++){ cout<<j;Sleep(s); }
			 for(int i=0;i<=6;i++){  gotoXY(x-7,y+i); cout<<e; Sleep(s); }
			 for(int i=0;i<=6;i++){  gotoXY(x+3,y+i); cout<<e; Sleep(s); }

			 switch(n){
            	 case 23:
            	     gotoXY(x-7,y-1); cout<<f;
            	     gotoXY(x-7,y+6); cout<<k;
            	     gotoXY(x+3,y-1); cout<<o;
            	     gotoXY(x+3,y+6); cout<<k;
            	     break;
            	 case 32:
            	     gotoXY(x-7,y-1); cout<<p;
            	 	 gotoXY(x-7,y+6); cout<<h;
            	     gotoXY(x+3,y-1); cout<<o;
            	     gotoXY(x+3,y+6); cout<<k;
            	     break;
                 default:

            	     gotoXY(x-7,y-1); cout<<l;
            	     gotoXY(x-7,y+6); cout<<k;
            	     gotoXY(x+3,y-1); cout<<l;
            	     gotoXY(x+3,y+6); cout<<k;
            	     break;
				}
			 coloraCasella(x,y,n);
           }
        for(int n=33,y=59,x=28;n<=39;n++,y-=7){
             resetColor();

             setColor(GooseGameTitleColor,color[GooseGameTitleColor].contrast);
             gotoXY(x-6,y-1); for(int i=1;i<=9;i++){ cout<<j;Sleep(s); }
             gotoXY(x-6,y+6); for(int i=1;i<=9;i++){ cout<<j;Sleep(s); }
			 for(int i=0;i<=6;i++){  gotoXY(x-7,y+i); cout<<e; Sleep(s); }
			 for(int i=0;i<=6;i++){  gotoXY(x+3,y+i); cout<<e; Sleep(s); }

			 switch(n){
            	 case 33:
            	     gotoXY(x-7,y-1); cout<<p;
            	     gotoXY(x-7,y+6); cout<<p;
            	     gotoXY(x+3,y-1); cout<<m;
            	     gotoXY(x+3,y+6); cout<<o;
            	     break;
            	 case 39:
            	 	 gotoXY(x-7,y-1); cout<<f;
            	 	 gotoXY(x-7,y+6); cout<<p;
            	     gotoXY(x+3,y-1); cout<<l;
            	     gotoXY(x+3,y+6); cout<<o;
            	     break;
                 default:
            	     gotoXY(x-7,y-1); cout<<p;
					 gotoXY(x-7,y+6); cout<<p;
            	     gotoXY(x+3,y-1); cout<<m;
            	     gotoXY(x+3,y+6); cout<<m;
            	     break;
				}
			 coloraCasella(x,y,n);
           }
        for(int n=40,y=17,x=38;n<=47;n++,x+=10){
             resetColor();

             setColor(GooseGameTitleColor,color[GooseGameTitleColor].contrast);
             gotoXY(x-6,y-1); for(int i=1;i<=9;i++){ cout<<j;Sleep(s); }
             gotoXY(x-6,y+6); for(int i=1;i<=9;i++){ cout<<j;Sleep(s); }
			 for(int i=0;i<=6;i++){  gotoXY(x-7,y+i); cout<<e; Sleep(s); }
			 for(int i=0;i<=6;i++){  gotoXY(x+3,y+i); cout<<e; Sleep(s); }

			 switch(n){
            	 case 40:
            	     gotoXY(x-7,y-1); cout<<l;
            	     gotoXY(x-7,y+6); cout<<o;
            	     gotoXY(x+3,y-1); cout<<l;
            	     gotoXY(x+3,y+6); cout<<o;
            	     break;
            	 case 47:
            	     gotoXY(x-7,y-1); cout<<l;
            	     gotoXY(x-7,y+6); cout<<o;
					 gotoXY(x+3,y-1); cout<<g;
            	     gotoXY(x+3,y+6); cout<<m;
            	     break;
                 default:
                 	 gotoXY(x-7,y-1); cout<<l;
                 	 gotoXY(x-7,y+6); cout<<k;
            	     gotoXY(x+3,y-1); cout<<l;
					 gotoXY(x+3,y+6); cout<<k;
            	     break;
				}
			 coloraCasella(x,y,n);
           }
        for(int n=48,y=24,x=108;n<=52;n++,y+=7){
             resetColor();

             setColor(GooseGameTitleColor,color[GooseGameTitleColor].contrast);
             gotoXY(x-6,y-1); for(int i=1;i<=9;i++){ cout<<j;Sleep(s); }
             gotoXY(x-6,y+6); for(int i=1;i<=9;i++){ cout<<j;Sleep(s); }
			 for(int i=0;i<=6;i++){  gotoXY(x-7,y+i); cout<<e; Sleep(s); }
			 for(int i=0;i<=6;i++){  gotoXY(x+3,y+i); cout<<e; Sleep(s); }

			 switch(n){
            	 case 48:
            	     gotoXY(x-7,y-1); cout<<o;
            	     gotoXY(x-7,y+6); cout<<k;
            	     gotoXY(x+3,y-1); cout<<m;
            	     gotoXY(x+3,y+6); cout<<m;
            	     break;
            	 case 52:
            	 	 gotoXY(x-7,y-1); cout<<o;
            	 	 gotoXY(x-7,y+6); cout<<k;
            	     gotoXY(x+3,y-1); cout<<m;
            	     gotoXY(x+3,y+6); cout<<i;
            	     break;
                 default:
            	     gotoXY(x-7,y-1); cout<<p;
					 gotoXY(x-7,y+6); cout<<p;
            	     gotoXY(x+3,y-1); cout<<m;
            	     gotoXY(x+3,y+6); cout<<m;
            	     break;
				}
			 coloraCasella(x,y,n);
           }
        for(int n=53,y=52,x=98;n<=58;n++,x-=10){
             resetColor();

             setColor(GooseGameTitleColor,color[GooseGameTitleColor].contrast);
             gotoXY(x-6,y-1); for(int i=1;i<=9;i++){ cout<<j;Sleep(s); }
             gotoXY(x-6,y+6); for(int i=1;i<=9;i++){ cout<<j;Sleep(s); }
			 for(int i=0;i<=6;i++){  gotoXY(x-7,y+i); cout<<e; Sleep(s); }
			 for(int i=0;i<=6;i++){  gotoXY(x+3,y+i); cout<<e; Sleep(s); }

			 switch(n){
            	 case 53:
            	     gotoXY(x-7,y-1); cout<<f;
            	     gotoXY(x-7,y+6); cout<<k;
            	     gotoXY(x+3,y-1); cout<<o;
            	     gotoXY(x+3,y+6); cout<<k;
            	     break;
            	 case 58:
            	     gotoXY(x-7,y-1); cout<<p;
            	 	 gotoXY(x-7,y+6); cout<<h;
            	     gotoXY(x+3,y-1); cout<<o;
            	     gotoXY(x+3,y+6); cout<<k;
            	     break;
                 default:

            	     gotoXY(x-7,y-1); cout<<l;
            	     gotoXY(x-7,y+6); cout<<k;
            	     gotoXY(x+3,y-1); cout<<l;
            	     gotoXY(x+3,y+6); cout<<k;
            	     break;
				}
			 coloraCasella(x,y,n);
           }
        for(int n=59,y=45,x=48;n<=61;n++,y-=7){
             resetColor();

             setColor(GooseGameTitleColor,color[GooseGameTitleColor].contrast);
             gotoXY(x-6,y-1); for(int i=1;i<=9;i++){ cout<<j;Sleep(s); }
             gotoXY(x-6,y+6); for(int i=1;i<=9;i++){ cout<<j;Sleep(s); }
			 for(int i=0;i<=6;i++){  gotoXY(x-7,y+i); cout<<e; Sleep(s); }
			 for(int i=0;i<=6;i++){  gotoXY(x+3,y+i); cout<<e; Sleep(s); }

			 switch(n){
            	 case 59:
            	     gotoXY(x-7,y-1); cout<<p;
            	     gotoXY(x-7,y+6); cout<<p;
            	     gotoXY(x+3,y-1); cout<<m;
            	     gotoXY(x+3,y+6); cout<<o;
            	     break;
            	 case 61:
            	 	 gotoXY(x-7,y-1); cout<<f;
            	 	 gotoXY(x-7,y+6); cout<<p;
            	     gotoXY(x+3,y-1); cout<<l;
            	     gotoXY(x+3,y+6); cout<<o;
            	     break;
                 default:
            	     gotoXY(x-7,y-1); cout<<p;
					 gotoXY(x-7,y+6); cout<<p;
            	     gotoXY(x+3,y-1); cout<<m;
            	     gotoXY(x+3,y+6); cout<<m;
            	     break;
				}
			 coloraCasella(x,y,n);
           }
        for(int n=62,y=31,x=58;n<=62;n++,x+=10){
             resetColor();

             setColor(GooseGameTitleColor,color[GooseGameTitleColor].contrast);
             gotoXY(x-6,y-1); for(int i=1;i<=9;i++){ cout<<j;Sleep(s); }
             gotoXY(x-6,y+6); for(int i=1;i<=9;i++){ cout<<j;Sleep(s); }
			 for(int i=0;i<=6;i++){  gotoXY(x-7,y+i); cout<<e; Sleep(s); }
			 for(int i=0;i<=6;i++){  gotoXY(x+3,y+i); cout<<e; Sleep(s); }

			 switch(n){
                 case 62:
                 	 gotoXY(x-7,y-1); cout<<l;
                 	 gotoXY(x-7,y+6); cout<<o;
            	     gotoXY(x+3,y-1); cout<<l;
					 gotoXY(x+3,y+6); cout<<k;
					 gotoXY(x+3,y);cout<<e;gotoXY(x+3,y+2);cout<<e;gotoXY(x+3,y+4);cout<<e;;
            	     break;
				}
			 coloraCasella(x,y,n);
           }

           y=31;x=68; int n=63;
           setColor(GooseGameTitleColor,color[GooseGameTitleColor].contrast);
           gotoXY(x-6,y-3); for(int i=1;i<=20;i++){ cout<<j;Sleep(s); }
           gotoXY(x-6,y+8); for(int i=1;i<=20;i++){ cout<<j;Sleep(s); }
		   for(int i=-2;i<=7;i++){  gotoXY(x-7,y+i); cout<<e; Sleep(s); }
		   for(int i=-2;i<=7;i++){  gotoXY(x+14,y+i); cout<<e; Sleep(s); }

		   for(int a=0;a<=6;a++){
		   	resetColor();
		   	gotoXY(x-6,y-2+a); cout<<"      ";
		   }

		    setColor(GooseGameTitleColor,color[GooseGameTitleColor].contrast);
		    gotoXY(x+3,y+1); cout<<"Ultima";
		    gotoXY(x+6,y+2); cout<<"Casella!";
		   for(int a=1;a<=6;a++){//Ciclo che controlla la posizione di tutti i giocatori
	    	int b=0;
			if(stats[a].pos==n){//Se il giocatore 'a' � su questa casella stampa il suo nome del suo colore e incrementa 'b' cos� che se un'altro giocatore e sulla stessa casella, viene messo in colonna
	    		gotoXY(x-6,y-2+b);//A 'y' viene sommato 'b' che di base vale 0, cos� da mettere in colonna i giocatori
	    		setColor(stats[a].color,color[stats[a].color].contrast);
	    		for(int f=0;f<strlen(stats[a].name)&&f<4;f++){//For() che stampa i primi 5 caratteri del nome per non andare fuori spazio
				cout<<stats[a].name[f];
				}
				resetColor();
	    		b++;//Incremento di 'b' cos� che il prossimo giocatore venga messo in colonna
			}

		}

    resetColor();
    }
     void coloraCasella(int x,int y,int n){//Riempie la casella del suo colore (nel caso sia una casella speciale) e dei nomi dei giocatori
        ///CONTROLLO POSIZIONE (n) CON LA POSIZIONE DELLE CASELLE SPECIALI E COLORAZIONE DI CONSEGUENZA
        for(int y1=y;y1<=y+5;y1++){
			 gotoXY(x-6,y1);
			 resetColor();//Imposta il colore del bg del colore della casella speciale;
			 cout<<"         ";/*stampa lo spazio vuoto interno della casella*/
			}

		if(ponte.pos==n){
			for(int y1=y;y1<=y+5;y1++){
			 gotoXY(x-6,y1);
			 setColor(ponte.color,color[ponte.color].contrast);//Imposta il colore del bg del colore della casella speciale;
			 cout<<"         ";/*stampa lo spazio vuoto interno della casella*/
			 if(y1==y){gotoXY(x,y);setColor(color[ponte.color].contrast,ponte.color); cout<<"P";}//Se sta stampando la prima riga vuota della casella, stampa anche le lettere speciali
			 resetColor();
			}
		}
		else if(locanda.pos==n){
		    for(int y1=y;y1<=y+5;y1++){
			 gotoXY(x-6,y1);
			 setColor(locanda.color,color[locanda.color].contrast);
			 cout<<"         "; if(y1==y){gotoXY(x,y);setColor(color[locanda.color].contrast,locanda.color); cout<<"LO";}
			 resetColor();
			}
		}
		else if(prigione.pos==n){
		 for(int y1=y;y1<=y+5;y1++){
			 gotoXY(x-6,y1);
			 setColor(prigione.color,color[prigione.color].contrast);
			 cout<<"         "; if(y1==y){gotoXY(x,y);setColor(color[prigione.color].contrast,prigione.color); cout<<"P";}
			 resetColor();
			}
		}
		else if(labirinto.pos==n){
		 for(int y1=y;y1<=y+5;y1++){
			 gotoXY(x-6,y1);
			 setColor(labirinto.color,color[labirinto.color].contrast);
			 cout<<"         "; if(y1==y){gotoXY(x,y);setColor(color[labirinto.color].contrast,labirinto.color); cout<<"LA";}
			 resetColor();
			}
		}
		else if(scheletro.pos==n){
		 for(int y1=y;y1<=y+5;y1++){
			 gotoXY(x-6,y1);
			 setColor(scheletro.color,color[scheletro.color].contrast);
			 cout<<"         "; if(y1==y){gotoXY(x,y);setColor(color[scheletro.color].contrast,scheletro.color); cout<<"S";}
			 resetColor();
			}
		}
	    else{gotoXY(x,y);cout<<n;}//Se non � una casella speciale stampa il numero della casella semplicemente

	    ///////RIEMPIMENTO CASELLA CON NOMI GIOCATORI////
	    int b=0;//Variabile da sommare alla 'y' per mettere in colonna i giocatori
	    for(int a=1;a<=6;a++){//Ciclo che controlla la posizione di tutti i giocatori

			if(stats[a].pos==n){//Se il giocatore 'a' � su questa casella stampa il suo nome del suo colore e incrementa 'b' cos� che se un'altro giocatore e sulla stessa casella, viene messo in colonna
	    		gotoXY(x-6,y+b);//A 'y' viene sommato 'b' che di base vale 0, cos� da mettere in colonna i giocatori
	    		setColor(stats[a].color,color[stats[a].color].contrast);
	    		for(int f=0;f<strlen(stats[a].name)&&f<4;f++){//For() che stampa i primi 5 caratteri del nome per non andare fuori spazio
				cout<<stats[a].name[f];
				}
				resetColor();
	    		b++;//Incremento di 'b' cos� che il prossimo giocatore venga messo in colonna
			}

		}
	 }

	 void drawPonte(){
	 	 int y=11;
	 	 setColor(0,ponte.color);

	 	 gotoXY(142,y++);cout<<"                                                           ";
	 	 gotoXY(142,y++);cout<<"                                                           ";
	 	 gotoXY(142,y++);cout<<"                                                           ";
	 	 gotoXY(142,y++);cout<<"                                                           ";
	 	 gotoXY(142,y++);cout<<"                                                           ";
	 	 gotoXY(142,y++);cout<<"         "<<a<<"                                 "<<a ;
	 	 gotoXY(142,y++);cout<<"         "<<a<<"                                 "<<a ;
	 	 gotoXY(142,y++);cout<<"         "<<a<<a<<a<<"                               "<<a ;
	 	 gotoXY(142,y++);cout<<"       "<<a<<" "<<b<<b<<b<<a<<" "<<a<<"                          "<<a<<b<<b ;
	 	 gotoXY(142,y++);cout<<"       "<<a<<b<<b<<b<<a<<b<<a<<a<<" "<<a<<" "<<a<<"            "<<a<<" "<<a<<" "<<a<<" "<<a<<" "<<a<<a<<a<<b<<"  ";
	 	 gotoXY(142,y++);cout<<"       "<<a<<b<<a<<a<<b<<b<<b<<b<<a<<a<<a<<a<<a<<" "<<a<<" "<<a<<" "<<a<<" "<<a<<"  "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<b<<b<<a;
	 	 gotoXY(142,y++);cout<<"       "<<" "<<a<<a<<a<<b<<b<<b<<a<<b<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<b<<b<<a<<b<<b<<b<<a<<b<<b<<b<<a<<a;
	 	 gotoXY(142,y++);cout<<"       "<<"   "<<a<<b<<b<<a<<b<<b<<b<<b<<a<<b<<b<<b<<a<<b<<b<<a<<b<<b<<b<<a<<b<<b<<b<<a<<b<<b<<b<<a<<a<<a;
	 	 gotoXY(142,y++);cout<<"       "<<"    "<<a<<a<<b<<a<<b<<a<<a<<b<<a<<b<<a<<a<<b<<a<<b<<a<<b<<a<<b<<a<<b<<a<<b<<a<<b<<a<<a;
	 	 gotoXY(142,y++);cout<<"              "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a;
	 	 gotoXY(142,y++);cout<<"                                                           ";
	 	 gotoXY(142,y++);cout<<"                                                           ";
	 	 gotoXY(142,y++);cout<<"                                                           ";
         gotoXY(149,y);
		 resetColor();cout<<"\t";
	    }

	  void drawLocanda(){
	  	 int y=11;
	 	 setColor(0,locanda.color);

	 	 gotoXY(142,y++);cout<<"                       "<<a<<a<<a<<a<<"       "<<b<<b<<b<<b;
	 	 gotoXY(142,y++);cout<<"                     "<<a<<a<<b<<b<<b<<b<<a<<a<<"     "<<b<<b<<b<<b;
	 	 gotoXY(142,y++);cout<<"                   "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<"   "<<a<<a<<a<<a;
	 	 gotoXY(142,y++);cout<<"                 "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<" "<<a<<"  "<<a;
	 	 gotoXY(142,y++);cout<<"               "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<"  "<<a;
	 	 gotoXY(142,y++);cout<<"             "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<a;
	 	 gotoXY(142,y++);cout<<"           "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a;
	 	 gotoXY(142,y++);cout<<"         "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a;
	 	 gotoXY(142,y++);cout<<"       "<<a<<a<<"  "<<a<<a<<"                        "<<a<<a<<"  "<<a<<a;
	 	 gotoXY(142,y++);cout<<"           "<<a<<a<<"  "<<a<<a<<a<<a<<"            "<<a<<a<<a<<a<<"  "<<a<<a;
	 	 gotoXY(142,y++);cout<<"           "<<a<<a<<"  "<<a<<b<<b<<a<<"            "<<a<<b<<b<<a<<"  "<<a<<a;
	 	 gotoXY(142,y++);cout<<"           "<<a<<a<<"  "<<a<<b<<b<<a<<"            "<<a<<b<<b<<a<<"  "<<a<<a;
	 	 gotoXY(142,y++);cout<<"           "<<a<<a<<"  "<<a<<a<<a<<a<<"            "<<a<<a<<a<<a<<"  "<<a<<a;
	 	 gotoXY(142,y++);cout<<"           "<<a<<a<<"         "<<a<<a<<a<<a<<a<<a         <<a<<a;
	 	 gotoXY(142,y++);cout<<"           "<<a<<a<<"         "<<a<<"    "<<a<<"         "<<a<<a;
	 	 gotoXY(142,y++);cout<<"           "<<a<<a<<"         "<<a<<"    "<<a<<"         "<<a<<a;
	 	 gotoXY(142,y++);cout<<"           "<<a<<a<<"         "<<a<<"    "<<a<<"         "<<a<<a;
	 	 gotoXY(142,y++);cout<<"           "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a;
         gotoXY(149,y);
		 resetColor();cout<<"\t";
	    }

	  void drawPrigione(){
	 	 int y=11;
	 	 setColor(0,prigione.color);
	 	 gotoXY(142,y++);cout<<"              "<<a<<a<<"      "<<a<<a<<"      "<<a<<a<<"      "<<a<<a;
	 	 gotoXY(142,y++);cout<<"              "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b<<b;
	 	 gotoXY(142,y++);cout<<"        "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a;
	 	 gotoXY(142,y++);cout<<"         "<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b;
	 	 gotoXY(142,y++);cout<<"              "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b;
	 	 gotoXY(142,y++);cout<<"              "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b;
	 	 gotoXY(142,y++);cout<<"              "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b;
	 	 gotoXY(142,y++);cout<<"        "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a;
	 	 gotoXY(142,y++);cout<<"         "<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b;
	 	 gotoXY(142,y++);cout<<"              "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b;
	 	 gotoXY(142,y++);cout<<"              "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b;
	 	 gotoXY(142,y++);cout<<"              "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b;
	 	 gotoXY(142,y++);cout<<"        "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a;
	 	 gotoXY(142,y++);cout<<"         "<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b;
	 	 gotoXY(142,y++);cout<<"              "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b;
	 	 gotoXY(142,y++);cout<<"              "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b;
	 	 gotoXY(142,y++);cout<<"              "<<a<<a<<b<<"     "<<a<<a<<b<<"     "<<a<<a<<b<<"     " <<a<<a<<b;
	 	 gotoXY(142,y++);cout<<"        "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a;
	 	 gotoXY(142,y++);cout<<"         "<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b;
	 	 gotoXY(142,y++);cout<<"               "<<b<<b<<"      "<<b<<b<<"      "<<b<<b<<"      "<<b<<b;
         gotoXY(149,y);
		resetColor();cout<<"\t";
	 }

	  void drawLabirinto(){
	  	 setColor(0,labirinto.color);
         int y=11;
	 	 gotoXY(142,y++);cout<<"       "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<b<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a;
	 	 gotoXY(142,y++);cout<<"       "<<a<<b<<b<<b<<b<<b<<b<<b<<a<<b<<b<<b<<b<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<b<<b<<b<<b<<b<<a;
	 	 gotoXY(142,y++);cout<<"       "<<a<<a<<b<<a<<a<<b<<b<<b<<a<<a<<b<<b<<b<<b<<a<<b<<b<<b<<b<<a<<a<<a<<b<<b<<b<<b<<b<<a<<b<<b<<b<<b<<b<<b<<a<<b<<b<<a;
	 	 gotoXY(142,y++);cout<<"       "<<a<<b<<b<<b<<a<<b<<b<<b<<b<<a<<a<<b<<b<<b<<a<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<b<<b<<b<<a;
	 	 gotoXY(142,y++);cout<<"       "<<a<<b<<b<<b<<a<<b<<b<<b<<b<<b<<a<<b<<b<<b<<b<<b<<b<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<b<<b<<b<<b<<a<<b<<a<<b<<b<<a;
	 	 gotoXY(142,y++);cout<<"       "<<a<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<b<<b<<b<<a<<b<<b<<a<<a<<a<<a<<a<<b<<b<<b<<a<<b<<b<<b<<a<<b<<b<<a<<b<<a<<b<<b<<a;
	 	 gotoXY(142,y++);cout<<"       "<<a<<b<<b<<b<<b<<b<<b<<a<<b<<b<<b<<b<<b<<b<<a<<b<<b<<b<<b<<b<<b<<a<<b<<b<<b<<a<<b<<b<<b<<a<<b<<b<<b<<b<<b<<b<<b<<a;
	 	 gotoXY(142,y++);cout<<"       "<<a<<b<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<b<<b<<a<<b<<b<<b<<a<<b<<b<<b<<a<<b<<b<<b<<a<<b<<b<<a<<a<<a<<a<<b<<a;
	 	 gotoXY(142,y++);cout<<"       "<<a<<b<<b<<b<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<b<<a<<a<<b<<b<<b<<a<<b<<b<<b<<a<<b<<b<<b<<b<<b<<b<<b<<a;
	 	 gotoXY(142,y++);cout<<"       "<<a<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<b<<b<<b<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<b<<b<<b<<a<<a<<a<<a<<a<<b<<a<<a<<a;
	 	 gotoXY(142,y++);cout<<"       "<<a<<b<<b<<b<<b<<b<<b<<a<<b<<b<<a<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a;
	 	 gotoXY(142,y++);cout<<"       "<<a<<a<<a<<b<<b<<b<<b<<a<<b<<b<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<b<<b<<b<<b<<b<<a;
	 	 gotoXY(142,y++);cout<<"       "<<a<<b<<b<<b<<b<<a<<a<<a<<b<<b<<a<<a<<a<<a<<a<<a<<a<<b<<b<<a<<a<<b<<b<<b<<b<<a<<b<<b<<b<<b<<b<<a<<b<<b<<b<<a<<a<<a;
	 	 gotoXY(142,y++);cout<<"       "<<a<<b<<b<<b<<a<<b<<b<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<a<<b<<b<<b<<b<<b<<a<<a<<a<<a<<b<<b<<a;
	 	 gotoXY(142,y++);cout<<"       "<<a<<b<<b<<b<<a<<b<<b<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<b<<b<<a;
	 	 gotoXY(142,y++);cout<<"       "<<a<<b<<b<<b<<a<<a<<b<<b<<b<<b<<a<<b<<b<<b<<b<<b<<a<<b<<b<<b<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<b<<b<<b<<a<<b<<b<<a;
	 	 gotoXY(142,y++);cout<<"       "<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a;
	 	 gotoXY(142,y++);cout<<"       "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<b<<b<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<b<<b<<b<<a<<a;
         gotoXY(149,y);
		 resetColor();cout<<"\t";
	    }

	  void drawScheletro(){
	  	 setColor(0,scheletro.color);
         int y=11;
	 	 gotoXY(142,y++);cout<<"                 "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a                ;
	 	 gotoXY(142,y++);cout<<"               "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<a             ;
	 	 gotoXY(142,y++);cout<<"             "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<a          ;
	 	 gotoXY(142,y++);cout<<"            "<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<a       ;
	 	 gotoXY(142,y++);cout<<"           "<<a<<b<<b<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<b<<b<<b<<b<<a       ;
	 	 gotoXY(142,y++);cout<<"          "<<a<<b<<b<<b<<b<<a<<a<<a<<a<<a<<b<<b<<b<<b<<b<<b<<b<<a<<a<<a<<a<<a<<b<<b<<b<<b<<b<<b<<a      ;
	 	 gotoXY(142,y++);cout<<"          "<<a<<b<<b<<b<<b<<a<<a<<b<<b<<b<<a<<b<<b<<b<<b<<b<<a<<b<<b<<b<<a<<a<<b<<b<<b<<b<<b<<b<<b<<a     ;
	 	 gotoXY(142,y++);cout<<"          "<<a<<b<<b<<b<<b<<b<<b<<a<<a<<a<<b<<b<<b<<b<<b<<b<<b<<a<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a     ;
	 	 gotoXY(142,y++);cout<<"          "<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<b<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a     ;
	 	 gotoXY(142,y++);cout<<"           "<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<b<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a      ;
	 	 gotoXY(142,y++);cout<<"            "<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a      ;
	 	 gotoXY(142,y++);cout<<"             "<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a       ;
	 	 gotoXY(142,y++);cout<<"               "<<a<<a<<a<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<b<<a<<a<<a        ;
	 	 gotoXY(142,y++);cout<<"                "<<a<<b<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<b<<a         ;
	 	 gotoXY(142,y++);cout<<"                "<<a<<b<<b<<a<<b<<b<<b<<a<<b<<b<<a<<b<<b<<a<<b<<b<<a<<b<<b<<a        ;
	 	 gotoXY(142,y++);cout<<"                 "<<a<<a<<b<<b<<a<<b<<b<<b<<a<<b<<b<<a<<b<<b<<a<<b<<b<<a;
	 	 gotoXY(142,y++);cout<<"                 "<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a<<a;
	 	 gotoXY(142,y++);cout<<"                                             ";
         gotoXY(149,y);
		 resetColor();cout<<"\t";
	    }
