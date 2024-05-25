#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<time.h>
#include<cmath>

using namespace std;


int main()
{
    

    const int rows = 4000; 
    const int cols = 3;

                                                    // File reading
    ifstream file1("driver-data.csv");
    string value;
    string* col1 = new string[rows + 1];
    int f = 0;
    string line1;
    getline(file1, line1);
                                                  // Reading the first column into string array because the ID is too big for int or double.
    while (!file1.eof()) {
        getline(file1, col1[f], ',');

        f++;
        getline(file1, value);
    }


    file1.close();

    ifstream jobfile("driver-data.csv");
    double num = 0;
    char comma;
                                                     // A double type array to read the next columns of the file.
    double* rawdata = new double[rows * cols] {0};
    int i = 0;

    string line;
    getline(jobfile, line);

    while (!jobfile.eof()) {
        jobfile >> num;
        jobfile >> comma;
        rawdata[i] = num;
        i++;

    }


    double** data = new double* [rows];                                // A 2D double type array to arrange data.
    for (int i = 0; i < rows; i++)
    {
        data[i] = new double[cols-1];
    }

    for (int i = 0, k = 1; i < rows; i++, k = k + 3)
    {
        for (int j = 0; j < 1; j++)
        {
            data[i][j] = rawdata[k];
        }
    }

    for (int i = 0, k = 2; i < rows; i++, k = k + 3)
    {
        for (int j = 1; j < 2; j++)
        {
            data[i][j] = rawdata[k];
        }
    }

  

    const int k = 3;                                        // Taking k = 3 as number of clusters.

    int* cluster_centre = new int[k];

    srand(time(0));

    for (int i = 0; i < k; i++)
    {
        cluster_centre[i] = rand() % 4000;                 // Randomly assigning the centroids.
    }

    for (int i = 0; i < k; i++)
    {
        cout << cluster_centre[i] << " ";                 // Printing the centroids.
    }
    cout << endl;
    int* repeated_cluster_centres = new int[k];

    

    int* cluster_value = new int[rows] {0};
    int count = 0;

    int k1_count = 0;        double k1_sumx = 0;           double k1_sumy = 0;
    int k2_count = 0;        double k2_sumx = 0;           double k2_sumy = 0;                // variables for x and y coordinates.
    int k3_count = 0;        double k3_sumx = 0;           double k3_sumy = 0;
    

    int check = 0;

    while (check != k)                               // The loop breaks when the centroids repeat.
    {
        k1_count = 0;         k1_sumx = 0;          k1_sumy = 0;
        k2_count = 0;         k2_sumx = 0;          k2_sumy = 0;
        k3_count = 0;         k3_sumx = 0;          k3_sumy = 0;
      
        count = 0;
        check = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < 1; j++)                // Loop for finding distance b/w points and assigning cluster number.
            {
                double distance1 = sqrt(pow((data[i][j] - data[cluster_centre[0]][j]), 2) + pow((data[i][j + 1] - data[cluster_centre[0]][j + 1]), 2));
                double distance2 = sqrt(pow((data[i][j] - data[cluster_centre[1]][j]), 2) + pow((data[i][j + 1] - data[cluster_centre[1]][j + 1]), 2));
                double distance3 = sqrt(pow((data[i][j] - data[cluster_centre[2]][j]), 2) + pow((data[i][j + 1] - data[cluster_centre[2]][j + 1]), 2));
                

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

                                                                    
        for (int i = 0; i < rows; i++)                                // Loop for calculating mean.     
        {
            if (cluster_value[i] == 1)
            {
                k1_count++;
                k1_sumx = k1_sumx + data[i][0];
                k1_sumy = k1_sumy + data[i][1];
            }

            if (cluster_value[i] == 2)
            {
                k2_count++;
                k2_sumx = k2_sumx + data[i][0];                         
                k2_sumy = k2_sumy + data[i][1];
            }

            if (cluster_value[i] == 3)
            {
                k3_count++;
                k3_sumx = k3_sumx + data[i][0];
                k3_sumy = k3_sumy + data[i][1];
            }

           

        }

        for (int i = 0; i < k; i++)                                     //Saving the cluster centres to check the repeating centres.
        {
            repeated_cluster_centres[i] = cluster_centre[i];
        }

      
        for (int i = 0; i < rows; i++)
        {
            if (data[i][0] == k1_sumx / k1_count && data[i][1] == k1_sumy / k1_count)
            {
                cluster_centre[0] = i;
            }
        }

        for (int i = 0; i < rows; i++)
        {
            if (data[i][0] == k2_sumx / k2_count && data[i][1] == k2_sumy / k2_count)
            {
                cluster_centre[1] = i;
            }
        }

        for (int i = 0; i < rows; i++)
        {
            if (data[i][0] == k3_sumx / k3_count && data[i][1] == k3_sumy / k3_count)
            {
                cluster_centre[2] = i;
            }
        }


        int temp = 0;


        for (int i = 0; i < k; i++)                                  // Sorting the arrays to compare if the values have repeated.
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

        for (int i = 0; i < k; i++)
        {
            if (repeated_cluster_centres[i] == cluster_centre[i])                       // Loop to check the repeated centres. 
            {
                check++;
            }
        }
        

    }


    cout << "\nCount : " << count << endl;


    int c = 0;

    for (int i = 0; i < rows; i++)
    {
        if (cluster_value[i] < 1 || cluster_value[i]>3)                                // Checking that the cluster number does not exceed K.
        {
            c++;
        }
    }

    cout << "\nC : " << c << endl;

    double** output_data = new double* [4000];                           // Created a new array to store all the data(including the cluster values).
    for (int i = 0; i < rows; i++)
    {
        output_data[i] = new double[4];
    }


    for (int i = 0, k = 0; i < rows; i++, k = k + 3)
    {
        for (int j = 0; j < 1; j++)
        {
            output_data[i][j] = rawdata[k];
        }
    }

    for (int i = 0, k = 1; i < rows; i++, k = k + 3)
    {
        for (int j = 1; j < 2; j++)
        {
            output_data[i][j] = rawdata[k];
        }
    }

    for (int i = 0, k = 2; i < rows; i++, k = k + 3)
    {
        for (int j = 2; j < 3; j++)
        {
            output_data[i][j] = rawdata[k];
        }
    }

    for (int i = 0, k = 3; i < rows; i++, k = k + 3)
    {
        for (int j = 3; j < 4; j++)
        {
            output_data[i][j] = cluster_value[i];
        }
    }


    ofstream myfile;
    myfile.open("output.csv");                                          // File writing

    myfile << line << ",cluster_value" << endl;



    for (int i = 0; i < rows; ++i)
    {
        myfile << col1[i] << ",";
        for (int j = 1; j < 4; ++j)
            if (j < (4 - 1)) {
                myfile << output_data[i][j] << ",";
            }
            else if (j == (4 - 1)) {
                myfile << output_data[i][j] << "\n";
            }
    }



    return 0;

}