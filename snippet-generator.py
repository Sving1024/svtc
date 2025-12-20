"""
snippet-generator

generate the snippets of all the files
"""

import pathlib


def gen(body: str, desc: str, trigger: str):
    l = body.split("\n")
    body_str = ""
    for x in l:
        if x.startswith("#include"):
            continue
        if (
            x.startswith("using ll =")
            or x.startswith("using ull")
            or x.startswith("using uint")
        ):
            continue
        body_str += f'"{x}",'
    body_str = body_str[:-1]
    return f'"{desc}": {{"prefix": "{trigger}","body": [{body_str}],"description": "{desc}"}}'


def main():
    cur_path = pathlib.Path(".")
    output = "{"
    for snippets in cur_path.rglob("*.hpp"):
        desc = snippets.name[:-4]
        output += gen(snippets.read_text(), desc, desc) + ","
    output = output[:-1]
    output += "}"
    with pathlib.Path("out.json").open("w", encoding="utf-8") as f:
        f.write(output)


main()
