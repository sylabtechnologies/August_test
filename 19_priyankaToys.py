# PY2

def toys(w) :
    if (len(w) < 1) :
        return 0
    if (len(w) == 1) :
        return 1

    w.sort()
    cutoff = w[0] + 4
    answer = 1

    for x in w[1:] :
        if x > cutoff :
            answer += 1
            cutoff = x + 4

    return answer
