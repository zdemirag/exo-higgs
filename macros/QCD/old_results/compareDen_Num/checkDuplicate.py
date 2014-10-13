with open('num.txt') as f:
    seen = set()
    for line in f:
        line_lower = line.lower()
        if line_lower in seen:
            print(line)
        else:
            seen.add(line_lower)
    with open('den.txt','r') as f2:
        for line2 in f2:
            line2_lower = line2.lower()
            if line2_lower in seen:
                print(line2)
            else:
                seen.add(line2_lower)
