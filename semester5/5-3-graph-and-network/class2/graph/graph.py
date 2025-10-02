from graphviz import Graph

g = Graph(format="png")

# nodeの準備
g.node("私")
g.node("配偶者")
g.node("参加者1")
g.node("参加者2")
g.node("参加者3")
g.node("参加者4")
g.node("参加者5")
g.node("参加者6")
g.node("参加者7")
g.node("参加者8")

# edgeを追加
g.edge("参加者2", "参加者3")
g.edge("参加者2", "参加者4")
g.edge("参加者2", "参加者5")
g.edge("参加者2", "参加者6")
g.edge("参加者2", "参加者7")
g.edge("参加者2", "参加者8")
g.edge("参加者2", "私")
g.edge("参加者2", "配偶者")

g.edge("参加者3", "参加者5")
g.edge("参加者3", "参加者6")
g.edge("参加者3", "参加者7")
g.edge("参加者3", "参加者8")
g.edge("参加者3", "私")
g.edge("参加者3", "配偶者")

g.edge("参加者6", "参加者7")
g.edge("参加者6", "参加者8")
g.edge("参加者6", "私")
g.edge("参加者6", "配偶者")

g.edge("参加者7", "私")
g.edge("参加者7", "配偶者")

g.render(view=True)

