#include <stdio.h>
#include <stdlib.h>
#include "../geometrie.h"

int main() {
    Point P, A, B;
    Segment S;
    double dp;

    printf("\nP x: ");
    scanf("%lf", &P.x);
    printf("\nP y: ");
    scanf("%lf", &P.y);
    printf("\nA x: ");
    scanf("%lf", &A.x);
    printf("\nA y: ");
    scanf("%lf", &A.y);
    printf("\nB x: ");
    scanf("%lf", &B.x);
    printf("\nB y: ");
    scanf("%lf", &B.y);

    affiche_point("P", P);
    affiche_point("A", A);
    affiche_point("B", B);

    S.A = A;
    S.B = B;

    dp = distance_segment_point(P, S);
    printf("Distance Segment AB: %lf\n", dp);

    return 0;
}
