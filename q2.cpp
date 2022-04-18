#include <iostream>
#include <fstream>
#include<string>
using namespace std;



int strln(char* str)   //function to calculate strln
{
	int sl= 0;//string length
	int a = 0;

	while (str[a] != '\0')//while loop to check condition
	{
		sl++;
		a++;
	}

	return sl;
}




char** ListOfWords(int testcases, int rfl)//decleration 
{
	ifstream file("Input.txt");//in[put call
	if (file)//condition
	{

		string momycal;//dreamy
		for (int i = 0; i < rfl; i++)      //it will skips all the data before words 
		{
			getline(file, momycal);
		}

		char** wordList = new char* [testcases];

		int i = 0;

		while (i < testcases)
		{
			char abc[80];

			file.getline(abc, 80);

			int cols = 0;
			cols = strln(abc);

			wordList[i] = new char[cols + 1];

			int j = 0;
			for (j = 0; j < cols; j++) //deep copying
			{
				wordList[i][j] = abc[j];
			}
			wordList[i][j] = '\0';
			i++;
		}

		return wordList;
	}

}


int* SearchAllDirections(char** grid, int gr, int gc, int row, int col, char* word)
{
	int rd[] = { 0, 0, 1,-1, 1, 1, -1, -1 };     // 8 directions  in the order (right to left),(left to right),(top to bottom),(bottom to top),(top left to bottom right),(top right to bottom left),(bottom left to top right),(bottom right to top left)
	int cd[] = { -1, 1, 0, 0, 1, -1, 1, -1 };

	int* arr = new int[3];    //this array will keep have 1 at 0 position if word is found and record of the end cordinates of the word
							 //if word not found then the array wil will have -1 at 0 position

	if (grid[row][col] != word[0])   //checks if the cordinate have the first letter of word 
	{
		arr[0] = -1;
		arr[1] = 0;
		arr[2] = 0;
		return  arr;
	}


	int length = strln(word);


	for (int i = 0; i < 8; i++)  //for 8 directions
	{
		int j;
		int moveRow = row + rd[i];//move row
		int moveCol = col +cd[i];//move columbs

		// First character is already checked, match remaining 
		// characters //being sorted 
		for (j = 1; j < length; j++)  //as first letter is found so starting form 1
		{
			// If out of pl ksidskbound break  //no to no
			if (moveRow >=gr || moveRow < 0 || moveCol >=gc || moveCol < 0)
			{
				break;
			}


			// If not matched,  break 
			if (grid[moveRow][moveCol] != word[j])
			{
				break;
			}



			moveRow = moveRow + rd[i];   //moves in the specuific direction 
			moveCol = moveCol +cd[i];
		}


		if (j == length) //if the word is found then j will be equal to length
		{
			moveRow = moveRow - rd[i];//moving condition
			moveCol = moveCol -cd[i];//check calll

			arr[0] = 1;
			arr[1] = moveRow;   //end cordinates of the word or column or row
			arr[2] = moveCol;

			return arr;
		}

	}
	arr[0] = -1;//condition
	arr[1] = 0;//condition
	
	arr[2] = 0;//condition
	return  arr;
}
char**rwsg(int rows, int cols, int rfl)
{
	ifstream file("Input.txt");
	if (file)
	{

		string momycal;
		for (int i = 0; i < rfl; i++) //this skips all the data before grid
		{
			getline(file, momycal);
		}

		int i = 0;
		char** Grid = new char* [rows];
		while (i < rows)
		{
			char abc[80];

			file.getline(abc, 80);



			Grid[i] = new char[cols + 1];

			int j = 0;
			int k = 0;
			for (j = 0; j < cols && k < (cols + cols - 1); j++) //deep copying
			{

				Grid[i][j] = abc[k];
				k += 2;

			}
			Grid[i][j] = '\0';
			i++;
		}

		return Grid;
	}

}


int* GridSearch(char** grid, int gr, int gc, char* word)  //it will  search all words for sure
{
	int* returna= new int[4];
	int* arr = new int[3];

	for (int row = 0; row <gr; row++)
	{
		for (int col = 0; col <gc; col++)
		{
			arr = SearchAllDirections(grid,gr,gc, row, col, word);
			if (arr[0] == 1)
			{
				returna[0] = row;  //start cordinates of word
				returna[1] = col;

				returna[2] = arr[1];  //end codinates of the word
				returna[3] = arr[2];
				return returna;
			}

		}

	}
	delete[]arr;
	returna[0] = -1;
	returna[1] = 0;
	returna[2] = 0;
	returna[3] = 0;
	return returna;

}


void ShowCordinates(char** list, int numberOfWords, char** grid, int rows, int cols)  //function to show start and cordinates  of a word
{
	ofstream file("Output.txt");
	if (file)
	{
		for (int i = 0; i < numberOfWords; i++)
		{

			int* resultArr = new int[4];

			resultArr = GridSearch(grid, rows, cols, list[i]);  //this function returns the cordinates

			if (resultArr[0] == -1)
			{
				file << "NOT FOUND";
			}
			else
			{
				file << "{" << resultArr[0] << "," << resultArr[1] << "}" << "{" << resultArr[2] << "," << resultArr[3] << "}";
			}
			file << endl;
			delete[]resultArr;


		}
	}
	file.close();


}
int  main()
{
	ifstream fin("input.txt");
	if (fin)
	{
		int r,c,t;

		fin >> r >> c >> t;
		

		cout <<"****INDEX SEARCHER****";

		int rw; 

		char** grid = 0;
		rw = 2;  //first line has rows and col second has testcases
		grid =rwsg(r, c, rw);     //reads the grid
		

		char** choice = 0;
		rw = 2 + r;  //list of words start after grid 
		choice = ListOfWords(t, rw);         //reads the list

		ShowCordinates(choice, t, grid, r, c);   
		cout << endl << "hurray !All Words Have Been Searched!\n YOU CAN GO AND CHECK UR FILE Check Your File:)\n";
	}
	
return 0;

}

