# PY2

def palyndrome(x) :
    if (len(x) <= 1) : return True
    if (x[0] != x[-1]) : return False
    return palyndrome(x[1:-1])

print palyndrome('anneivotemorecarsracerometovienna')
