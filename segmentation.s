global load_lgdt

load_lgdt:
    lgdt [esp + 4]
    ret


