#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<time.h>
#include<cmath>
using namespace std;



int main()
{
    const int rows = 200;
    const int cols = 3;                                         
                         
    
                                                                 // File reading 
    ifstream file1("segmented_customers-1.csv"); 
    string value;
    string *col1=new string[rows+1];
    int f = 0;
    string line1;
    getline(file1, line1);
    
    while (!file1.eof()) {
        getline(file1, col1[f], ','); 
        
        f++;
        getline(file1, value);
    }


    file1.close();

    ifstream file("segmented_customers-1.csv");

   
    string *col=new string[rows+1];
    string *col2=new string[rows+1];
    int** data = new int* [rows];

    for (int i = 0; i < rows; i++)
    {
        data[i] = new int[cols] {0};
    }
    
    int i = 0, j = 0, t = 0, l = 0;

    

    string line;
    getline(file, line);

    
    int num = 0;
   
    char comma;
    

    while (!file.eof())
    {
        
        getline(file, col[i], ',');
       
        getline(file, col2[i], ',');

       
        i++;
        
        file >> num;
        file >> comma;
        data[t][l] = num;
        l++;
        file >> num;
        file >> comma;
        data[t][l] = num;
        l++;
        file >> num;
        file >> comma;
        data[t][l] = num;
        l = 0;
        t++;
        
    }

    // Taking k = 3 as number of clusters.
    const int k = 3;

    int* cluster_centre = new int[k];

    srand(time(0));
    // Randomly assigning the centroids.
    for (int i = 0; i < k; i++)
    {
        cluster_centre[i] = rand() % 200;
    }
    // Printing the centroids.
    for (int i = 0; i < k; i++)
    {
        cout << cluster_centre[i] << " ";
    }
    cout << endl;
    int* repeated_cluster_centres = new int[k];

   

    int* cluster_value = new int[rows] {0};
    int count = 0;

    // variables for x,y and z coordinates.

    int k1_count = 0;        double k1_sumx = 0;           double k1_sumy = 0;            double k1_sumz = 0;
    int k2_count = 0;        double k2_sumx = 0;           double k2_sumy = 0;            double k2_sumz = 0;
    int k3_count = 0;        double k3_sumx = 0;           double k3_sumy = 0;            double k3_sumz = 0;
    

    int check = 0;

    while (check != k)                    // The loop breaks when the centroids repeat.
    {
    {
        k1_count = 0;         k1_sumx = 0;          k1_sumy = 0;          k1_sumz = 0;
        k2_count = 0;         k2_sumx = 0;          k2_sumy = 0;          k2_sumz = 0;
        k3_count = 0;         k3_sumx = 0;          k3_sumy = 0;          k3_sumz = 0;

        count = 0;
        check = 0;
       
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < 1; j++)                            // Loop for finding distance b/w points and assigning cluster number.
            {
                double distance1 = sqrt(pow((data[i][j] - data[cluster_centre[0]][j]), 2) + pow((data[i][j + 1] - data[cluster_centre[0]][j + 1]), 2) + pow((data[i][j + 2] - data[cluster_centre[0]][j + 2]), 2));
                double distance2 = sqrt(pow((data[i][j] - data[cluster_centre[1]][j]), 2) + pow((data[i][j + 1] - data[cluster_centre[1]][j + 1]), 2) + pow((data[i][j + 2] - data[cluster_centre[1]][j + 2]), 2));
                double distance3 = sqrt(pow((data[i][j] - data[cluster_centre[2]][j]), 2) + pow((data[i][j + 1] - data[cluster_centre[2]][j + 1]), 2) + pow((data[i][j + 2] - data[cluster_centre[2]][j + 2]), 2));
                

                if (distance1 < distance2)
                {
                    if (distance1 < distance3)
                    {
                      
                            cluster_value[i] = 1;
                            count++;
                       
                    }
                }
                if (distance2 < distance1)
                {
                    if (distance2 < distance3)
                    {
                       

                            cluster_value[i] = 2;
                            count++;
                        
                    }
                }
                if (distance3 < distance1)
                {
                    if (distance3 < distance2)
                    {
                       

                            cluster_value[i] = 3;
                            count++;
                        
                    }
                }
               
            }
        }

        // Loop for calculating mean. 
        for (int i = 0; i < rows; i++)
        {
            if (cluster_value[i] == 1)
            {
                k1_count++;
                k1_sumx = k1_sumx + data[i][0];
                k1_sumy = k1_sumy + data[i][1];
                k1_sumz = k1_sumz + data[i][2];

            }

            if (cluster_value[i] == 2)
            {
                k2_count++;
                k2_sumx = k2_sumx + data[i][0];
                k2_sumy = k2_sumy + data[i][1];
                k2_sumz = k2_sumz + data[i][2];
            }

            if (cluster_value[i] == 3)
            {
                k3_count++;
                k3_sumx = k3_sumx + data[i][0];
                k3_sumy = k3_sumy + data[i][1];
                k3_sumz = k3_sumz + data[i][2];
            }



        }
        //Saving the cluster centres to check the repeating centres.
        for (int i = 0; i < k; i++)
        {
            repeated_cluster_centres[i] = cluster_centre[i];
        }


        for (int i = 0; i < rows; i++)
        {
            if (data[i][0] == k1_sumx / k1_count && data[i][1] == k1_sumy / k1_count && data[i][2] == k1_sumz / k1_count)
            {
                cluster_centre[0] = i;
            }
        }

        for (int i = 0; i < rows; i++)
        {
            if (data[i][0] == k2_sumx / k2_count && data[i][1] == k2_sumy / k2_count && data[i][2] == k2_sumz / k2_count)
            {
                cluster_centre[1] = i;
            }
        }

        for (int i = 0; i < rows; i++)
        {
            if (data[i][0] == k3_sumx / k3_count && data[i][1] == k3_sumy / k3_count && data[i][2] == k3_sumz / k3_count)
            {
                cluster_centre[2] = i;
            }
        }
   

        int temp = 0;
        // Sorting the arrays to compare if the values have repeated.

        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k; j++)
            {
                if (cluster_centre[i] < cluster_centre[j])
                {
                    temp = cluster_centre[i];
                    cluster_centre[i] = cluster_centre[j];
                    cluster_centre[j] = temp;
                }
            }
        }


        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k; j++)
            {
                if (repeated_cluster_centres[i] < repeated_cluster_centres[j])
                {
                    temp = repeated_cluster_centres[i];
                    repeated_cluster_centres[i] = repeated_cluster_centres[j];
                    repeated_cluster_centres[j] = temp;
                }
            }
        }
        // Loop to check the repeated centres. 
        for (int i = 0; i < k; i++)
        {
            if (repeated_cluster_centres[i] == cluster_centre[i])
            {
                check++;
            }
        }

    }


    cout << "\nCount : " << count << endl;


    int c = 0;
    // Checking that the cluster number does not exceed K.
    for (int i = 0; i < rows; i++)
    {
        if (cluster_value[i] < 1 || cluster_value[i]>3)
        {
            cluster_value[i] = 1;
            c++;
        }
    }

    cout << "\nC : " << c << endl;
    // Created a new array to store all the data(including the cluster values).
    int** output_data = new int* [200];
    for (int i = 0; i < rows; i++)
    {
        output_data[i] = new int[4];
    }


    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            output_data[i][j] = data[i][j];
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 1; j < 2; j++)
        {
            output_data[i][j] = data[i][j];
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 2; j < 3; j++)
        {
            output_data[i][j] = data[i][j];
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 3; j < 4; j++)
        {
            output_data[i][j] = cluster_value[i];
        }
    }

   
    // File writing

    ofstream myfile;
    myfile.open("output1.csv");

    myfile << "CustomerID,Gender,Age,Income,Score,cluster" << endl;

    for (int i = 0; i < rows; ++i)
    {
        myfile << col1[i] << "," << col2[i] << ",";
        for (int j = 0; j < 4; ++j)
        {    
            if (j < (4 - 1)) {
                myfile << output_data[i][j] << ",";
            }
            else if (j == (4 - 1)) {
                myfile << output_data[i][j] << "\n";
            }
        }
    }




    return 0;
}
