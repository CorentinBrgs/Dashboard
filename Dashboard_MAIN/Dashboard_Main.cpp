// Used for memory-mapped functionality
#include <windows.h>
#include "sharedmemory.h"


#include <stdio.h>
#include <conio.h>
#include <cstdlib>

//used for Serial control
#include <tchar.h>
#include "SerialClass.h"	// Library described above
#include <string>

// Name of the pCars memory mapped file
#define MAP_OBJECT_NAME "$pcars$"

#define SERIALPORT "COM3" /*If you choose to set the port manually
                            change the port here.
                            IMPORTANT ! For COM port above 9, correct value is \\\\.\\COMx
                            */
#define MAX_ATTEMPT 100 //Number of attempt to open the mapped memory file


int main(int argc, _TCHAR* argv[])
{
	//------------------------------------------------------------------------
	// Opening Shared Memory file and ensure it's ok.
	//------------------------------------------------------------------------

	//Testing if it's possible to open the mapped memory fill. After MAX_ATTEMPT the programm stops.
	bool SharedMemoryIsOpened = 0; //
	int attemptCounter = 1; //count number of times the shared memory setup failed.
							//If larger than MAX_ATTEMPT the programms stops

	while(!SharedMemoryIsOpened)
	{
        HANDLE fileHandle = OpenFileMapping( PAGE_READONLY, FALSE, MAP_OBJECT_NAME );
        system("cls");
        printf("Trying to open the Mapped Memory File (attempt %d/%d)", attemptCounter, MAX_ATTEMPT);
		Sleep(1000);
        attemptCounter++;
        if (attemptCounter>=MAX_ATTEMPT) {
			printf("Trying to open the Mapped Memory File (attempt %d/%d) : FAILED\n\n", attemptCounter, MAX_ATTEMPT);
			attemptCounter = 0;
			return 1;
        }
        SharedMemoryIsOpened = !(fileHandle==NULL);
        CloseHandle(fileHandle);
	}

	//Opening the mapped memory file
    HANDLE fileHandle = OpenFileMapping( PAGE_READONLY, FALSE, MAP_OBJECT_NAME );

    // Get the data structure
    const SharedMemory* sharedData = (SharedMemory*)MapViewOfFile( fileHandle, PAGE_READONLY, 0, 0, sizeof(SharedMemory) );
    if (sharedData == NULL)
    {
        printf( "Could not map view of file (%d).\n", GetLastError() );
        CloseHandle( fileHandle );
        return 1;
    }

    // Ensure we're sync'd to the correct data version
    if ( sharedData->mVersion != SHARED_MEMORY_VERSION )
    {
        printf( "Data version mismatch\n");
        return 1;
    }

	printf(" : SUCCESS\n");
	attemptCounter = 0;

	//------------------------------------------------------------------------------
	//Setup the serial connection with the Arduino.
	//------------------------------------------------------------------------------

	//Pour une connection manuelle via la saisie du port COM dans le define
 /*   Serial* SP = NULL;
    do { //while the device is not connected, attempt to connect
		attemptCounter++;
		printf("Trying to connect to serial Port %s (attempt %d/%d) : ", SERIALPORT, attemptCounter, MAX_ATTEMPT);
        SP = new Serial(SERIALPORT);    // adjust as needed
		if (!SP->IsConnected()){
            Sleep(5000);
            system("cls");
		}
	} while(!(SP->IsConnected()) && (attemptCounter<MAX_ATTEMPT));

	//printf("SUCCESS\n");
	Sleep(1000);
*/

	//Auto research from available COM Ports
    Serial* SP = NULL; //Initialisation du port série
    char portSerieCom[6] = "COM0";
    int numCOM = 0+48; //0=48 in ASCII table.
    char portCOMDispo[150] = "Ports COM disponibles : ";

    do {
        printf("Trying to connect to %s : ", portSerieCom);
        SP = new Serial(portSerieCom);
            //SP = new Serial("COM0");
	    if (SP->IsConnected()){
            printf("SUCCESS\n");
            SP->~Serial(); //Destructeur de l'objet Serial pour fermer le port ouvert
            strcat(portCOMDispo, portSerieCom);
            strcat(portCOMDispo, " / ");

        }
        numCOM++;
        portSerieCom[3] = numCOM;
    } while(numCOM<10+48);  //(!SP->IsConnected())&&(


    strcat(portCOMDispo, "\n -> enter the COM Port number (for COM0 type 0) : ");
    printf("%s", portCOMDispo);
    bool portIsCorrect = false ;
    while (!portIsCorrect) {
        scanf("%d", &numCOM);//saisir le port com souhaité ; si le port c'est pas disponible il est demandé à l'utilisateur de recommencer la saisie.
        portIsCorrect = !(strchr(portCOMDispo, numCOM+48)==NULL);
        if(!portIsCorrect)
            printf("Incorrect entry !\n -> enter the COM Port number (for COM0 type 0) : ");
    }
    portSerieCom[3] = numCOM+48;
    SP = new Serial(portSerieCom); //ouverture du port série
    if (SP->IsConnected()){
        printf("Port %s connected with success", portSerieCom); //confirmation de l'ouverture du port
    }
	Sleep(1000);

	//---------------------------------------------------------------------------------
	// application reads from the specified serial port and reports the collected data
	//---------------------------------------------------------------------------------

	char incomingData[256] = "";	// don't forget to pre-allocate memory
	printf("%s\n",incomingData);	//print number of data currently in the buffer
	int dataLength = 255;	//max string length to print each time
	int readResult = 0;		//returns true if data in the buffer
	bool WriteIsOk = 0;		//self-explaining ; useful for debugging only

	printf( "ESC TO EXIT\n\n");

	while(true) //tant que le Dashboard est connecté
	{
	    //printf("%d \n", (int((sharedData->mRpm)/10) != int(mRpm/10)));

        //------------------------------------------------------------------------------
        // Enable it if you want the programm to read what Arduino sends.
        // May slow the programm
        //------------------------------------------------------------------------------

        /*readResult = SP->ReadData(incomingData,dataLength);
        if (readResult) {
            printf("%s\n",incomingData);
            //printf("Bytes read: (%d)\n",readResult);
        }
        incomingData[readResult] = 0;*/

        //------------------------------------------------------------------------------
        // Acquire data from game
        // Print to console
        // Send to arduino
        //------------------------------------------------------------------------------

        /*printf("mGameState: (%d)\n", sharedData->mGameState );
        printf("mSessionState: (%d)\n", sharedData->mSessionState );
        printf("mRaceState: (%d)\n\n", sharedData->mRaceState );
        printf (" mGear : (%d)\n", sharedData->mGear );
        printf(" mNumGears : (%d)\n", int(sharedData->mNumGears));
        printf(" mRpm : (%d)\n", int((sharedData->mRpm)));
        printf(" mMaxRpm : (%d)\n", int((sharedData->mMaxRPM)));
        printf(" mSpeed : (%d)\n", int((sharedData->mSpeed)*3.6));
        printf(" mThrottle : (%d)\n", int((sharedData->mThrottle)*100));
        printf(" mBrake : (%d)\n", int((sharedData->mBrake)*100));*/


        //int mGameState = sharedData->mGameState ;
        //int mSessionState = sharedData->mSessionState;
        //int mRaceState = sharedData->mRaceState;
        //int rpmGraph = (mRpm>6000)*9*(mRpm-6000)/(mMaxRPM-6000);
        //int mThrottle = int((sharedData->mThrottle)*100);
        //int mBrake = int((sharedData->mBrake)*100);
        int mGear = sharedData->mGear;
        int mRpm = int(sharedData->mRpm);
        int mMaxRPM = int(sharedData->mMaxRPM);
        int mSpeed = int((sharedData->mSpeed)*3.6);
        int mPosition = sharedData->mParticipantInfo[0].mRacePosition;

        printf("%d\n", mGear);
        printf("%d\n", mRpm);
        printf("%d\n", mMaxRPM);

        printf("%s\n", sharedData->mParticipantInfo[0].mName);
        printf("%d\n", mPosition);

        char buffer[40]; //buffer contenant les données à envoyer. Chaine de caractère : attention à la taille de la chaine pour éviter les débordements
        //format de donnée à utiliser : '/%,%,%,%;'
        sprintf(buffer, "/%d,%d,%d,%d;", mSpeed, mRpm, mMaxRPM, mGear); //buffer envoye a l'arduino
        unsigned int nbChar = strlen (buffer);

        WriteIsOk = SP->WriteData(buffer, nbChar);
        //printf("WriteDataOk = %d\n", WriteIsOk); //si besoin de débugger l'écriture série

		if ( _kbhit() && _getch() == 27 ) // check for escape
		{
			break;
		}

		Sleep(20); //evite le débordement du buffer / 20=50hz
		system("cls");

	}

	//------------------------------------------------------------------------------
	// Cleanup
	//------------------------------------------------------------------------------
	UnmapViewOfFile( sharedData );
	CloseHandle( fileHandle );

	return 0;
}
