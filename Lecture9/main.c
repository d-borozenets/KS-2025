#include <mpi.h>
#include <stdio.h>
#include <unistd.h>
//4.1
// int main(int argc, char** argv) {
//     MPI_Init(&argc, &argv);
//
//     int rank, size;
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//     // Ця демка працює тільки для 2 процесів
//     if (size != 2) {
//         if (rank == 0)
//             printf("Запустіть програму з  2 процесами: mpirun -np 2 <шлях>\n");
//         MPI_Finalize();
//         return 0;
//     }
//
//     if (rank == 0) {
//         int data = 123;
//
//         printf("Rank 0: надсилаю значення %d до rank 1...\n", data);
//
//         MPI_Send(&data,        // адреса буфера
//                  1,            // count
//                  MPI_INT,      // datatype
//                  1,            // dest (одержувач)
//                  0,            // tag
//                  MPI_COMM_WORLD);
//
//         printf("Rank 0: повідомлення надіслано.\n");
//     }
//     else if (rank == 1) {
//         int received = 0;
//
//         MPI_Recv(&received,    // буфер прийому
//                  1,            // count
//                  MPI_INT,      // datatype
//                  0,            // source
//                  0,            // tag
//                  MPI_COMM_WORLD,
//                  MPI_STATUS_IGNORE);
//
//         printf("Rank 1: отримав значення %d від rank 0.\n", received);
//     }
//
//     MPI_Finalize();
//     return 0;
// }

//6.1
// int main(int argc, char** argv) {
//     MPI_Init(&argc, &argv);
//
//     int rank, size;
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     MPI_Comm_size(MPI_COMM_WORLD, &size);
//
//     // Імітуємо різну швидкість процесів
//     // Наприклад, rank 0 "повільний"
//     if (rank == 0) {
//         printf("Rank 0: виконую довгі обчислення...\n");
//         sleep(3);   // 3 секунди "роботи"
//         printf("Rank 0: дійшов до бар’єру\n");
//     }
//     else {
//         printf("Rank %d: готовий одразу\n", rank);
//         printf("Rank %d: чекаю повільні процеси...\n", rank);
//     }
//
//     // Кожен процес зупиниться тут, доки всі інші не виконають Barrier
//     MPI_Barrier(MPI_COMM_WORLD);
//
//     // Після бар'єру всі процеси продовжують одночасно
//     printf("Rank %d: пройшов бар’єр і продовжую виконання\n", rank);
//
//     MPI_Finalize();
//     return 0;
// }
/*int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Кожен процес має своє "локальне значення"
    int local_value = rank + 1;   // Наприклад: 1,2,3,4,...

    printf("Rank %d: local_value = %d\n", rank, local_value);

    int global_sum = 0;

    // Об'єднання всіх часткових значень (сума)
    MPI_Reduce(&local_value,   // адреса локального значення
               &global_sum,    // адреса результату (тільки на root)
               1,              // count
               MPI_INT,        // datatype
               MPI_SUM,        // операція зведення
               0,              // root (одержувач результату)
               MPI_COMM_WORLD);// комунікатор

    // Тільки root (rank 0) отримує результат
    if (rank == 0) {
        printf("Rank 0: глобальна сума = %d\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}*/