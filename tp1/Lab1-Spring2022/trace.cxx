/// Code élémentaire pour le calcul de la trace d'une matrice.
/// Printemps 2022
/// Objectif : manipuler les éléments de base du C++
///            utiliser des outils de profiling et de débogage
/// ref: l'exercice est inspiré très largement de ressources WWW             

#include <cstdlib>
#include <iostream>
#include <functional>

double** initialization(int);
double* fill_vectors(double**, int);
void print_matrix(double** , int);
double* trace (double** , int);
double* solve_euler_explicite (int, double, double (*phi) (double,double));
double* solve_euler_implicite (int, double, double (*phi) (double,double));
void display_soluce(double* , int);
double phi(double x, double u_x)
{
    return 2.0 * x * u_x;
}


/// Driver principal pour le calcul de la tace d'une matrice 
int main()
{
  int i, j, n;
  double **matrix;
  double* sum ;

  std::cout << std::endl << "Enter the Dimension for a square matrix: " << std::flush;
  std::cin >> n;
  matrix = initialization(n);
  print_matrix(matrix , n);
  for(i = 1 ; i < n ; i++)
      matrix[i] =  fill_vectors(&matrix[i] , n);
  sum = trace(matrix , n);
  print_matrix(matrix , n);
  std::cout << std::endl << "Sum of the diagonal elements are: " << *sum << std::endl;
  for (j=0; j<n; j++)
      free(matrix[j]);
  free(matrix);
  free(sum);

  int nbr_iter = 20;
  double cond_init = 1.0;

  double* solution_edo_explicite = solve_euler_explicite(nbr_iter, cond_init, &phi);
  std::cout << std::endl << "Solution of EOD with Euler Explicite : " << std::endl;
  display_soluce(solution_edo_explicite, nbr_iter);
  free(solution_edo_explicite);

  //double* solution_edo_implicite = solve_euler_implicite(nbr_iter, cond_init, &phi);
  //std::cout << std::endl << "Solution of EOD with Euler Implicite : " << std::endl;
  //display_soluce(solution_edo_implicite, nbr_iter);
  //free(solution_edo_implicite);

  return 0;
}


/// @brief Routine d'initialization qui permet d'allouer la mémoire pour une 
///        matrice carrée de taille n et renvoie un pointer vers 
///        la matrice allouée
/// @param[in] n est la taille souhaitée de la matrice
/// @return    Renvoie le pointeur vers la matrice allouée
double** initialization(int n)
{
  int i;
  double** matrix ;
  matrix = (double **)(calloc(n, sizeof(double *)));
  for(i=0 ; i< n ; i++)
    matrix[i] = (double *)(calloc(n, sizeof(double)));
  return (matrix);
}

/// @brief Intitialise un vecteur avec des valeurs aléatoires comprises
///        entre dans l'intervalle [-10;10]
/// @param[in] vec est le vecteur à initialiser
/// @param[in] n   est la taille du vecteur à initialiser
/// @return    Renvoie le vecteur initialisé.
double* fill_vectors(double** vec , int n)
{
  int i ;
  for(i = 0 ; i < n ; i++)
      (*vec)[i] = rand() % 20 - 10 ;
  return *vec;
}

/// @brief Affiche les éléments d'une matrice de taille n
/// @param[in] matrix est la matrice à afficher
/// @param[in] n est la taille de la matrice à afficher
void print_matrix(double** matrix , int n)
{
  int i,j;
  for (i= 0 ; i< n ; i++) {
    for(j = 0 ; j < n ; j++)
      std::cout << matrix[i][j] << ", ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

/// @brief Calcul la trace d'une matrice
/// @param[in] matrix est la matrice dont on souhaite connaître la trace.
/// @param[in] n est la taille de la matrice.
double* trace (double** matrix , int n)
{
  int i ;
    auto* sum = (double *)(calloc(1, sizeof(double)));
  for(i=1 ; i<n ; i++)
    *sum+=matrix[i][i];
  return sum;
}

/// @brief Affiche les éléments d'une liste de taille n
/// @param[in] array est la liste à afficher
/// @param[in] n est la taille de la liste
void display_soluce(double* array, int n) {
    for (int i = 0; i < n+1; i++) {
        std::cout << array[i] << ", ";
    }
    std::cout << std::endl;
}

/// @brief Resolution d'une EDO avec la méthode Euler Explicite
///@param[in] nbr_iter est le nombre d'itération
///@param[in] cond_init est la condition initiale
///@param[in] phi est la fonction qui nous donne la dérivée
///@return  Renvoie une array contenant les solution de l'EDO
double* solve_euler_explicite (int nbr_iter, double cond_init, double (*phi) (double,double))
{
    auto* solution = (double *) (malloc(nbr_iter + 1 * sizeof(double)));
    solution[0] = cond_init;
    double h = 1.0/nbr_iter;
    for (int i = 0; i < nbr_iter + 1; i++) {
        solution[i+1] = solution[i] + h * phi((double) i * h, solution[i]);
    }
    return solution;
}

/// @brief Resolution d'une EDO avec la méthode Euler Implicite
///@param[in] nbr_iter est le nombre d'itération
///@param[in] cond_init est la condition initiale
///@param[in] phi est la fonction qui nous donne la dérivée
///@return  Renvoie une array contenant les solution de l'EDO
double* solve_euler_implicite (int nbr_iter, double cond_init, double (*phi) (double,double))
{
    auto* solution_implicite = (double *) (malloc(nbr_iter + 1 * sizeof(double)));
    solution_implicite[0] = cond_init;
    double h = 1.0/nbr_iter;
    for (int i = 0; i < nbr_iter + 1; i++) {

        solution_implicite[i+1] = solution_implicite[i] + h * phi((double) i * h, solution_implicite[i]);
    }
    return solution_implicite;
}
