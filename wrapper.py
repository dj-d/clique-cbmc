import os


def run():
    os.system('cd cbmc && ./cbmc ../main.c --trace > ../file.log')


def get_output(vertex):
    file = open("file.log", "r")
    lines = file.read().split("\n")
    file.close()

    for line in lines:
        if "vertex[" in line:
            line = line.replace("l", "")
            line = line.replace(" ", "")

            line = line[:-34]

            if len(line) > 0:
                i = int(line[7])

                if '=-1' in line:
                    value = -1
                else:
                    value = int(line[10])

                vertex[i] = value

    return vertex

def clean():
    os.system('rm file.log')


if __name__ == '__main__':
    run()

    vertex = [0, 0, 0, 0, 0]

    print(get_output(vertex))

    clean()