#include "cJSON.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define LOCALSET_FILE (char *)"./localset.json"

/**
 *  \brief 读出文件中的所有内容（malloc）
 *
 *  一次性读出文件
 *
 *  \param file 文件
 *  \param int *len 文件长度
 *  \return 文件内容的指针，最后需要free
 */
char *ReadFile(char *file, int *len)
{
    FILE *f;
    char *data;

    f = fopen(file, "rb");
    if (f == NULL) {
        fprintf(stderr, "open file failed\n");
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    *len = ftell(f);
    data = (char *)malloc((*len + 1) * sizeof(char));
    rewind(f);
    *len = fread(data, 1, *len, f);
    data[*len] = '\0';
    fclose(f);

    return data;
}

/**
 *  \brief 将字符串一次性写入文件
 *  \param file 文件
 *  \param out 要写入的字符串
 *  \return
 */
int WriteFile(char *file, char *out)
{
    FILE *f = NULL;

    f = fopen(file, "w");
    if (f == NULL) {
        fprintf(stderr, "open file failed\n");
        return -1;
    }
    fprintf(f, "%s", out);

    if (f != NULL)
        fclose(f);

    return 0;
}

/* Parse text to JSON, then render back to text, and print! */
void testPrintJson(char *text)
{
    char *out;
    cJSON *json;

    json = cJSON_Parse(text);
    if (!json) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
    }
    else {
        out = cJSON_Print(json);
        cJSON_Delete(json);
        printf("%s\n", out);
        free(out);
    }
}

/**
 *  \brief 详细解析一下测试中的localset.json 文件
 *  \param text, localset.json 中通过ReadFile 读出来的字符串
 *  \return
 */

void testParseLocalset(char *text)
{
    int i, j;
    cJSON *json = NULL;
    cJSON *test = NULL;

    json = cJSON_Parse(text);
    if (!json) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
    }
    else {
        test = cJSON_GetObjectItemCaseSensitive(json, "test");
        if (cJSON_IsString(test) && (test->valuestring != NULL)) {
            printf("Checking monitor \"%s\"\n", test->valuestring);
        }

        for (i = 0; i < 4; i++) {
            char tmp[12];
            cJSON *index = NULL;
            int size = 0;
            cJSON *tmpindex = NULL;

            sprintf(tmp, "%d", i);
            /* printf("tmp=%s\n", tmp); */

            tmpindex = cJSON_GetObjectItemCaseSensitive(json, tmp);
            if (NULL == tmpindex) {
                printf(" tmpindex null\n");
                return;
            }

            size = cJSON_GetArraySize(tmpindex);
            /* printf("size=%d\n", size); */

            cJSON *name = cJSON_GetObjectItemCaseSensitive(tmpindex, "name");
            if (!cJSON_IsString(name) || name->valuestring == NULL) {
                printf("null(string) name \n");
                return;
            }

            cJSON *value = cJSON_GetObjectItemCaseSensitive(tmpindex, "value");
            if (!cJSON_IsString(value) || value->valuestring == NULL) {
                printf("null(string) value \n");
                return;
            }

            printf("index=%d name=%s value=%s\n", i, name->valuestring,
                   value->valuestring);
        }

        cJSON_Delete(json);
    }
}

/**
 *  \brief 修改localset.json 文件
 *  \param text, localset.json 中通过ReadFile 读出来的字符串
 *  \return
 */
void testModifyLocalset(char *text)
{
    int i, j;
    cJSON *json = NULL;
    cJSON *test = NULL;
    char *out;

    json = cJSON_Parse(text);
    if (!json) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
    }
    else {
        test = cJSON_GetObjectItemCaseSensitive(json, "test");
        if (cJSON_IsString(test) && (test->valuestring != NULL)) {
            printf("test = %s\n", test->valuestring);
        }
        if (0 == strcmp(test->valuestring, "wqivb")) {
            stpcpy(test->valuestring, "hello");
        }
        else if (0 == strcmp(test->valuestring, "hello")) {
            stpcpy(test->valuestring, "wqivb");
        }
        printf("modfy test = %s\n", test->valuestring);

        out = cJSON_Print(json);
        printf("after modify:%s\n", out);
        WriteFile(LOCALSET_FILE, out);

        free(out);

        cJSON_Delete(json);
    }
}

int main(int argc, char *argv[])
{
    char *json_text;
    int json_len;

    json_text = ReadFile(LOCALSET_FILE, &json_len);
    if (NULL == json_text || 0 == json_len) {
        printf("ReadFile error \n");
        return -1;
    }

    testPrintJson(json_text);
    testParseLocalset(json_text);
    testModifyLocalset(json_text);

    free(json_text);
    return 0;
}
