#include <cstdio>
#include <omp.h>
#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>

#define lli long long int

void server(std::string& query, omp_lock_t* write_lock, omp_lock_t* read_lock);
void client(std::vector<std::string>& tasks, std::string& query, omp_lock_t* write_lock, omp_lock_t* read_lock);

int main(int argc, char *argv[])
{
    omp_lock_t write_lock, read_lock;

    omp_init_lock(&write_lock);
    omp_init_lock(&read_lock);
    omp_set_lock(&read_lock);
    std::string query;
    std::vector<std::string> tasks {
            "5 + 3",
            "res / 2",
            "24 / res",
            "res * res",
            "NULL"};
    #pragma omp parallel shared(query)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                server(query, &write_lock, &read_lock);
            }
            #pragma omp section
            {
                client(tasks, query, &write_lock, &read_lock);
            }
        }
    }
}


void server(std::string& query, omp_lock_t* write_lock, omp_lock_t* read_lock)
{
    std::string s, str_temp = "", temp_s = "";
    int res = 0, term1 = 0, term2 = 0;
    int op = -1; // 0: +, 1: -, 2: *, 3: /
    while(true){
        omp_set_lock(read_lock);

        if (query[0] == 'N')
        {
            std::cout << res;
            return;
        }

        if (query[0] == 'r')
        {
            term1 = res;
            str_temp = "";
            int index = 3;
            while (true)
            {
                temp_s = query[index];
                index++;
                if (temp_s == "+" || temp_s == "-" || temp_s == "*" || temp_s == "/")
                {
                    op = temp_s == "+" ? 0 :
                         temp_s == "-" ? 1 :
                         temp_s == "*" ? 2 : 3;
                    continue;
                }
                if (temp_s == "r")
                {
                    str_temp = "res";
                    break;
                }
                if (temp_s != " ")
                    str_temp += temp_s;
                if (index == query.length())
                    break;
            }

            term2 = str_temp == "res" ? res : std::stoi(str_temp);
        } else
        {
            temp_s = "";
            int index = 0;
            str_temp = "";
            while (true)
            {
                temp_s = query[index];
                if (temp_s == "+" || temp_s == "-" || temp_s == "*" || temp_s == "/")
                {
                    op = temp_s == "+" ? 0 :
                         temp_s == "-" ? 1 :
                         temp_s == "*" ? 2 : 3;
                    index++;
                    break;
                }
                if (index == query.length())
                    break;
                index++;
                if (temp_s != " ")
                    str_temp += temp_s;
            }
            term1 = std::stoi(str_temp);
            str_temp = "";
            while (true)
            {
                temp_s = query[index];
                if (temp_s == "r")
                {
                    str_temp = "res";
                    break;
                }
                if (index == query.length())
                    break;
                index++;
                if (temp_s != " ")
                    str_temp += temp_s;
            }
            term2 = str_temp == "res" ? res : std::stoi(str_temp);
        }
        switch (op)
        {
            case 0:
                res = term1 + term2;
                break;
            case 1:
                res = term1 - term2;
                break;
            case 2:
                res = term1 * term2;
                break;
            case 3:
                res = term1 / term2;
                break;
            default:break;
        }
        omp_unset_lock(write_lock);
    }

}

void client(std::vector<std::string>& tasks, std::string& query, omp_lock_t* write_lock, omp_lock_t* read_lock)
{
    for (const auto &task : tasks)
    {
        omp_set_lock(write_lock);
        query = task;
        omp_unset_lock(read_lock);
    }
}
