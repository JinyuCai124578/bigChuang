import graphscope
from graphscope.dataset import load_ldbc

# 创建一个新的交互会话，载入LDBC示例图数据
# 随后返回一个Gremlin查询提交入口
sess = graphscope.session(num_workers=2)
graph = load_ldbc(sess, prefix='/path/to/ldbc_sample')
interactive = sess.gremlin(graph)

# 下面两句Gremlin示例查询分别计算图中顶点和边的总数
node_num = interactive.execute('g.V().count()').one()
edge_num = interactive.execute("g.E().count()").one()
