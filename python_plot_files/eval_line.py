def eval_line(line):
    line = line.split()
    new_line = []
    for i in line:
        new_line.append(eval(i))
    return new_line
