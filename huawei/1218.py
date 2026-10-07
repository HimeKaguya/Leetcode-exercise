# 题意简述：
# - 棋盘 M 行 N 列，起点固定为左上角 (0,0)，终点为右下角 (M-1, N-1)
# - 初始在起点为「兵」，只能上下左右走 1 格
# - 走到驿站 S 时，可「选择」花 1 步在同格变为「马」（马也可花 1 步变回兵）
# - 「马」按国际象棋日字格走 8 个方向
# - 障碍 X 不可进入；'.' 表示空地
# - 求最少步数，无法到达则输出 -1

from collections import deque

KNIGHT_MOVES = [
    (-2, -1), (-2, 1), (-1, -2), (-1, 2),
    (1, -2), (1, 2), (2, -1), (2, 1),
]
SOLDIER_MOVES = [(-1, 0), (1, 0), (0, -1), (0, 1)]

DIR_NAME = {
    (-1, 0): "上",
    (1, 0): "下",
    (0, -1): "左",
    (0, 1): "右",
}

# 牛客讨论「华为 9.21 笔试」第二题中的两个测试盘面
# 来源：https://www.nowcoder.com/discuss/402780098053644288
NOWCODER_CASES = [
    {
        "name": "案例一：牛客 9×9 大样例（多障碍 + 2 个驿站）",
        "grid": [
            list("........."),
            list(".....XXX."),
            list(".....X.X."),
            list(".....X.X."),
            list(".....X.XS"),
            list("XXXXXX.XX"),
            list("S........"),
            list("........."),
            list("........."),
        ],
    },
    {
        "name": "案例二：牛客帖中 3×2 小盘（理解兵直走、不必变身）",
        "grid": [
            list(".."),
            list(".X"),
            list("S."),
        ],
    },
]


def is_valid(x, y, m, n):
    return 0 <= x < m and 0 <= y < n


def grid_from_rows(rows):
    """从字符矩阵解析障碍、驿站、终点。"""
    m, n = len(rows), len(rows[0])
    obstacles, stables = set(), set()
    for i in range(m):
        for j in range(n):
            if rows[i][j] == "X":
                obstacles.add((i, j))
            elif rows[i][j] == "S":
                stables.add((i, j))
    return m, n, (m - 1, n - 1), obstacles, stables, rows


def piece_name(is_knight):
    return "马" if is_knight else "兵"


def describe_move(is_knight, dx, dy, x, y, nx, ny):
    if not is_knight:
        return f"兵向{DIR_NAME[(dx, dy)]}走 1 格：({x},{y}) → ({nx},{ny})"
    return f"马走日字：({x},{y}) → ({nx},{ny})"


def bfs(m, n, end, obstacles, stables):
    """只求最短步数（OJ 提交用）。"""
    steps, _ = bfs_with_path(m, n, end, obstacles, stables)
    return steps


def bfs_with_path(m, n, end, obstacles, stables):
    """
    BFS 并记录最优路径。
    返回 (步数, 路径列表)，路径每项为 dict：pos, piece, action
    """
    start = (0, 0, 0)  # x, y, is_knight
    queue = deque([start])
    visited = [[[-1, -1] for _ in range(n)] for _ in range(m)]
    parent = {}  # (x,y,k) -> (px,py,pk, action_str)
    visited[0][0][0] = 0

    while queue:
        x, y, is_knight = queue.popleft()
        steps = visited[x][y][is_knight]

        if (x, y) == end:
            path = []
            cur = (x, y, is_knight)
            while cur in parent:
                px, py, pk, action = parent[cur]
                path.append({
                    "pos": (cur[0], cur[1]),
                    "piece": piece_name(cur[2]),
                    "action": action,
                })
                cur = (px, py, pk)
            path.append({
                "pos": (0, 0),
                "piece": "兵",
                "action": "起点",
            })
            path.reverse()
            return steps, path

        moves = KNIGHT_MOVES if is_knight else SOLDIER_MOVES
        for dx, dy in moves:
            nx, ny = x + dx, y + dy
            if not is_valid(nx, ny, m, n) or (nx, ny) in obstacles:
                continue
            nxt = steps + 1
            if visited[nx][ny][is_knight] != -1 and visited[nx][ny][is_knight] <= nxt:
                continue
            visited[nx][ny][is_knight] = nxt
            parent[(nx, ny, is_knight)] = (
                x, y, is_knight,
                describe_move(is_knight, dx, dy, x, y, nx, ny),
            )
            queue.append((nx, ny, is_knight))

        if (x, y) in stables:
            other = 1 - is_knight
            nxt = steps + 1
            if visited[x][y][other] != -1 and visited[x][y][other] <= nxt:
                continue
            visited[x][y][other] = nxt
            from_p, to_p = piece_name(is_knight), piece_name(other)
            parent[(x, y, other)] = (
                x, y, is_knight,
                f"在驿站 S({x},{y}) 消耗 1 步变身：{from_p} → {to_p}（位置不变）",
            )
            queue.append((x, y, other))

    return -1, []


def print_grid(grid, highlight=None):
    """打印棋盘；highlight 为 {(r,c): 标记}。"""
    m, n = len(grid), len(grid[0])
    highlight = highlight or {}
    print("    ", end="")
    for j in range(n):
        print(f" {j} ", end="")
    print()
    for i in range(m):
        print(f" {i} ", end="")
        for j in range(n):
            ch = grid[i][j]
            if (i, j) == (0, 0):
                ch = "起" if ch == "." else ch
            elif (i, j) == (m - 1, n - 1):
                ch = "终" if ch == "." else ch
            if (i, j) in highlight:
                ch = highlight[(i, j)]
            print(f" {ch} ", end="")
        print()


def run_case(case):
    """运行单个牛客样例并打印逐步走法。"""
    name = case["name"]
    grid = case["grid"]
    m, n, end, obstacles, stables, grid = grid_from_rows(grid)

    print("=" * 60)
    print(name)
    print("=" * 60)
    print(f"棋盘大小：{m} 行 × {n} 列")
    print(f"起点：(0,0)  终点：{end}  驿站 S：{sorted(stables)}  障碍 X：{len(obstacles)} 个")
    print("\n【初始棋盘】（起=起点，终=终点）")
    print_grid(grid)

    steps, path = bfs_with_path(m, n, end, obstacles, stables)
    if steps < 0:
        print("\n结果：无解 (-1)")
        return

    print(f"\n【最短步数】{steps}")
    print("\n【逐步走法】")
    for i, step in enumerate(path):
        r, c = step["pos"]
        mark = {step["pos"]: "●"}
        print(f"\n--- 第 {i} 步后：位于 ({r},{c})，当前为【{step['piece']}】 ---")
        print(f"    操作：{step['action']}")
        if i > 0:
            print("    棋盘位置（●=当前）：")
            print_grid(grid, highlight=mark)

    print("\n【路径坐标序列】")
    coords = [step["pos"] for step in path]
    pieces = [step["piece"] for step in path]
    print("    " + " → ".join(f"({r},{c})[{p}]" for (r, c), p in zip(coords, pieces)))


def parse_grid():
    m, n = map(int, input().split())
    grid = []
    for _ in range(m):
        row = input().split()
        if len(row) == 1 and len(row[0]) == n:
            row = list(row[0])
        elif len(row) != n:
            row = list("".join(row).replace(" ", ""))
        grid.append(row)

    obstacles, stables = set(), set()
    for i in range(m):
        for j in range(n):
            if grid[i][j] == "X":
                obstacles.add((i, j))
            elif grid[i][j] == "S":
                stables.add((i, j))
    return m, n, (m - 1, n - 1), obstacles, stables


if __name__ == "__main__":
    import sys

    # Windows 终端默认编码可能导致中文乱码
    if hasattr(sys.stdout, "reconfigure"):
        try:
            sys.stdout.reconfigure(encoding="utf-8")
        except Exception:
            pass

    # python 1218.py        → 跑牛客两个内置样例并打印详细步骤
    # python 1218.py oj     → 从标准输入读 OJ 数据，只输出最短步数
    if len(sys.argv) > 1 and sys.argv[1] == "oj":
        m, n, end, obstacles, stables = parse_grid()
        print(bfs(m, n, end, obstacles, stables))
    else:
        for case in NOWCODER_CASES:
            run_case(case)
            print()
