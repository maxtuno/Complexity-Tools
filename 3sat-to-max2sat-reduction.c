/*
///////////////////////////////////////////////////////////////////////////////
//        Copyright (c) 2012-2020 Oscar Riveros. all rights reserved.        //
//                        oscar.riveros@peqnpx.science                       //
//                                                                           //
//   without any restriction, Oscar Riveros reserved rights, patents and     //
//  commercialization of this knowledge or derived directly from this work.  //
///////////////////////////////////////////////////////////////////////////////

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

struct cpu {
    int n;
    int m;
    int *Z;
    int **FF;
};

void reduction(struct cpu *cpu) {
    int i, j, k, d = cpu->n;
    printf("c if instance is satisfiable the optimum is %d\n", 10 * cpu->m - 7 * cpu->m);
    printf("p cnf %d %d\n", cpu->n + cpu->m, 10 * cpu->m);
    for (i = 0; i < cpu->m; i++) {
        d++;
        printf("%d 0\n", d);
        for (j = 0; j < cpu->Z[i]; j++) {
            printf("%d 0\n", cpu->FF[i][j]);
        }
        for (j = 0; j < cpu->Z[i]; j++) {
            printf("%d %d 0\n", cpu->FF[i][j], -d);
        }
        for (j = 0; j < cpu->Z[i] - 1; j++) {
            for (k = j + 1; k < cpu->Z[i]; k++) {
                printf("%d %d 0\n", -cpu->FF[i][j], -cpu->FF[i][k]);
            }
        }
    }
}

int main(int argc, char **argv) {

    printf("c ///////////////////////////////////////////////////////////////////////////////\n");
    printf("c //        Copyright (c) 2012-2020 Oscar Riveros. all rights reserved.        //\n");
    printf("c //                        oscar.riveros@peqnpx.science                       //\n");
    printf("c //                                                                           //\n");
    printf("c //   without any restriction, Oscar Riveros reserved rights, patents and     //\n");
    printf("c //  commercialization of this knowledge or derived directly from this work.  //\n");
    printf("c ///////////////////////////////////////////////////////////////////////////////\n");

    int i, j;
    char buffer[32];
    struct cpu cpu;

    if (argc != 2) {
        printf("usage: %s <instance>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (strcmp(buffer, "c") == 0) {
        while (strcmp(buffer, "\n") != 0) {
            fscanf(file, "%s", buffer);
        }
    }
    while (strcmp(buffer, "p") != 0) {
        fscanf(file, "%s", buffer);
    }
    fscanf(file, " cnf %i %i", &cpu.n, &cpu.m);
    cpu.Z = (int *) calloc((size_t) cpu.m, sizeof(int));
    cpu.FF = (int **) calloc((size_t) cpu.m, sizeof(int *));
    for (i = 0; i < cpu.m; i++) {
        j = 0;
        cpu.FF[i] = (int *) calloc((size_t) cpu.n, sizeof(int));
        do {
            fscanf(file, "%s", buffer);
            if (strcmp(buffer, "c") == 0) {
                continue;
            }
            cpu.FF[i][j++] = atoi(buffer);
        } while (strcmp(buffer, "0") != 0);
        j--;
        cpu.FF[i] = (int *) realloc(cpu.FF[i], j * sizeof(int));
        cpu.Z[i] = j;
    }
    fclose(file);

    reduction(&cpu);

    free(cpu.Z);
    free(cpu.FF);

    return EXIT_SUCCESS;
}