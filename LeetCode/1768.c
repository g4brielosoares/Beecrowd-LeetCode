#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *mergeAlternately(char *word1, char *word2) {
    int tamanho1 = strlen(word1);
    int tamanho2 = strlen(word2);
    int mergedSize = tamanho1 + tamanho2;
    char *merged = malloc((mergedSize + 1) * sizeof(char));
    int i = 0, j = 0, k = 0;

    while (i < mergedSize) {
        if (j < tamanho1) {
            merged[i++] = word1[j++];
        }
        if (k < tamanho2) {
            merged[i++] = word2[k++];
        }
    }
    merged[i] = '\0';
    return merged;
}

void print(char word[]) {
    for (int i = 0; word[i] != '\0'; i++) {
        printf("%c", word[i]);
    }
    printf("\n");
}

int main() {
    char word1[100], word2[100];

    scanf("%[^\n] %[^\n]", word1, word2);
    print(mergeAlternately(word1, word2));

    return 0;
}