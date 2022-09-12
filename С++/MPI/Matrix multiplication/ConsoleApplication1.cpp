#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>


int main(int argc, char* argv[])
{
    int i, j, k, l;
    int* Matr_1, * Matr_2, * Result_matr, * Buffer, * Ans;
    int Size = 5;
    int Rank_proc, Num_procs, Line;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &Rank_proc);
    MPI_Comm_size(MPI_COMM_WORLD, &Num_procs);

    Line = Size / Num_procs;
    Matr_1 = (int*)malloc(sizeof(int) * Size * Size);
    Matr_2 = (int*)malloc(sizeof(int) * Size * Size);
    Result_matr = (int*)malloc(sizeof(int) * Size * Size);
    Buffer = (int*)malloc(sizeof(int) * Size * Line);
    Ans = (int*)malloc(sizeof(int) * Size * Line);

    if (Rank_proc == 0){
        
        printf("Matr 1:\n");
        for (i = 0; i < Size; i++) {
            for (j = 0; j < Size; j++) {
                Matr_1[i * Size + j] = rand() % 10;
                printf("%4d", Matr_1[i * Size + j]);
            }
            printf("\n");
        }
        
            

        printf("Matr 2:\n");
        for (i = 0; i < Size; i++) {
            for (j = 0; j < Size; j++) {
                Matr_2[i * Size + j] = rand() % 10;
                printf("%4d", Matr_2[i * Size + j]);
            }
            printf("\n");
        }
        for (i = 1; i < Num_procs; i++){
            MPI_Send(Matr_2, Size * Size, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        for (l = 1; l < Num_procs; l++){
            MPI_Send(Matr_1 + (l - 1) * Line * Size, Size * Line, MPI_INT, l, 1, MPI_COMM_WORLD);
        }
        for (k = 1; k < Num_procs; k++){
            MPI_Recv(Ans, Line * Size, MPI_INT, k, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (i = 0; i < Line; i++){
                for (j = 0; j < Size; j++){
                    Result_matr[((k - 1) * Line + i) * Size + j] = Ans[i * Size + j];
                }
            }
        }
        for (i = (Num_procs - 1) * Line; i < Size; i++){
            for (j = 0; j < Size; j++){
                int temp = 0;
                for (k = 0; k < Size; k++) {
                    temp += Matr_1[i * Size + k] * Matr_2[k * Size + j];
                }
                Result_matr[i * Size + j] = temp;
            }
        }

        printf("Result:\n");
        for (i = 0; i < Size; i++) {
            for (j = 0; j < Size; j++) {
                printf("%4d ", Result_matr[i * Size + j]);
            }  
            printf("\n");           
        }


        free(Matr_1);
        free(Matr_2);
        free(Result_matr);
        free(Buffer);
        free(Ans);
    }
    else{
        MPI_Recv(Matr_2, Size * Size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        MPI_Recv(Buffer, Size * Line, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (i = 0; i < Line; i++){
            for (j = 0; j < Size; j++){
                int temp = 0;
                for (k = 0; k < Size; k++) {
                    temp += Buffer[i * Size + k] * Matr_2[k * Size + j];
                } 
                Ans[i * Size + j] = temp;
            }
        }
        MPI_Send(Ans, Line * Size, MPI_INT, 0, 3, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}