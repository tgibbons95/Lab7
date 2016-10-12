//Thomas Gibbons
//Oct 9, 2016
#include <iostream>
#include <cstring>
#include <stdio.h>

class Signal{
	private:
		int* signalData;
		int Max;
		int Length;
		double average;
		void mean();
		int readFile(char*);
	public:
		void Save_file(char*);
		void Sig_info();
		Signal();
		Signal(int);
		Signal(char*);
		~Signal();
};

Signal::Signal(){
	std::cout << "No File number or name given\n";
}

Signal::Signal(int inputFile){
	std::cout << "Testing";
	char* filename=new char[15];
	std::cout << "Testing";
	if(inputFile<10)
		sprintf(filename,"Raw_data_0%d.txt",inputFile);
	else
		sprintf(filename,"Raw_data_%d.txt",inputFile);
	readFile(filename);
	std::cout << "Testing";
	delete[] filename;
	std::cout << "Testing";
}

Signal::Signal(char* filename){
	readFile(filename);
}

Signal::~Signal(){
	delete[] signalData;
}

int Signal::readFile(char* filename){
	FILE *fp;
	fp=fopen(filename,"r");

	if(fp==NULL)
	{
		std::cout << std::endl << filename << "could not be accessed\n";
		return 1;
	}

	fscanf(fp,"%d %d",&Length,&Max);
	int tempCount=Length;

	signalData=new int[Length];
	int x=0;

	while(tempCount>0)
	{
		fscanf(fp,"%d", signalData[x]);
		x++;
		tempCount--;
	}

	fclose(fp);
	
	mean();
}

void Signal::mean(){
	int total=0;
	int tempCount=Length;
	
	while(tempCount>0)
	{
		total+=*(signalData+Length-tempCount);
		tempCount--;
	}
	average= (double) total/Length;
}

void Signal::Sig_info(){
	std::cout 	<< "\nLength: " << Length
				<< "\nMaximum: " << Max
				<< "\nAverage: " << average << std::endl;
}

void Signal::Save_file(char* filename){
	FILE *write;
	
	write=fopen(filename,"w");

	fprintf(write,"%d %d\n",Length, Max);
	
	int x=0;
	int tempCount=Length;
	while(tempCount>0)
	{
		fprintf(write,"%.4f\n",signalData[x]);
		x++;
		tempCount--;
	}

	fclose(write);
	
	std::cout << std::endl << filename << " has been saved\n";
}

int main(int argc, char** argv)
{
	Signal dataSample(5);
	dataSample.Sig_info();
	
	return 1;
}
