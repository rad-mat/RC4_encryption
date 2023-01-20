#include <string>
#include <iostream>
#include <fstream>
using namespace std;

void RC4( string file_name, string K );

int main()
{ 
    system( "dir toConvert /b > files.txt" );
    ifstream fileNames( "files.txt" );

    string fileName;
    while( getline( fileNames, fileName ) ) 
        RC4( fileName, "haslohaslo" );

    fileNames.close();
    system( "del files.txt" );
}

void RC4( string file_name, string K )
{
    ifstream txt( "toConvert\\" + file_name, ios_base::binary);
    if( !txt )
    {
        cerr << "ERROR opening file" << file_name << endl;
        return;
    }

    int S[256];
    int i = 0;
    int j = 0;

    for( ; i <= 255; i++ )
        S[i] = i;

    for( i = 0; i <= 255; i++ )
    {
        j = ( j + S[i] + K[i % K.length()] ) % 256;
        int temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }

    cout << "Przetwarzanie pliku " << file_name << endl;
    ofstream coded( "converted\\" + file_name, ios_base::binary );
    int c = i = j = 0;
    while( true )
    {
        if( ( c = txt.get() ) == EOF ) break;
        i = ( i + 1 ) % 256;
        j = ( j + S[i] ) % 256;
        int temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        coded << char( c ^ ( S[( S[i] + S[j] ) % 256] ) );
    }

    coded.close();
    txt.close();
}