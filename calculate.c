#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp = fopen("orig.txt", "r");
    FILE *output = fopen("output.txt", "w");
    if (!fp) {
        printf("ERROR opening input file orig.txt\n");
        exit(0);
    }
    int i = 0;
    char append[50], find[50], total[50];
    double orig_sum_a = 0.0, orig_sum_f = 0.0, orig_a, orig_f, orig_t, orig_total=0.0;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %s %lf %lf %lf\n", append, find,total, &orig_a, &orig_f,&orig_t);
        orig_sum_a += orig_a;
        orig_sum_f += orig_f;
	orig_total=orig_sum_a+orig_sum_f;
    }
    fclose(fp);

    fp = fopen("opt.txt", "r");
    if (!fp) {
        fp = fopen("orig.txt", "r");
        if (!fp) {
            printf("ERROR opening input file opt.txt\n");
            exit(0);
        }
    }
    double opt_sum_a = 0.0, opt_sum_f = 0.0, opt_a, opt_f, opt_total=0.0, opt_t;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %s %lf %lf %lf\n", append, find,total , &opt_a, &opt_f,&opt_t);
        opt_sum_a += opt_a;
        opt_sum_f += opt_f;
	opt_total=opt_sum_a+opt_sum_f;
    }

    fclose(fp);

 fp = fopen("opt_struct.txt", "r");
    if (!fp) {
        fp = fopen("orig.txt", "r");
        if (!fp) {
            printf("ERROR opening input file opt.txt\n");
            exit(0);
        }
    }
    double opt_struct_sum_a = 0.0, opt_struct_sum_f = 0.0, opt_struct_a, opt_struct_f, opt_struct_total=0.0, opt_struct_t;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %s %lf %lf %lf\n", append, find,total , &opt_struct_a, &opt_struct_f,&opt_struct_t);
        opt_struct_sum_a += opt_struct_a;
        opt_struct_sum_f += opt_struct_f;
	opt_struct_total=opt_struct_sum_a+opt_struct_sum_f;
    }
    fprintf(output, "append() %lf %lf %lf\n",orig_sum_a / 100.0, opt_struct_sum_a / 100.0, opt_sum_a / 100.0);
    fprintf(output, "findName() %lf %lf %lf\n", orig_sum_f / 100.0, opt_struct_sum_f / 100.0, opt_sum_f / 100.0);
	fprintf(output, "total %lf %lf %lf",orig_total / 100.0, opt_struct_total / 100.0,opt_total / 100.0);
    fclose(output);
    fclose(fp);

    return 0;
}
