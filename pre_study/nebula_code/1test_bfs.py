from nebula3.gclient.net import ConnectionPool
from nebula3.Config import Config
import pandas as pd
from typing import Dict
from nebula3.data.ResultSet import ResultSet

def result_to_df(result: ResultSet) -> pd.DataFrame:
    """
    build list for each column, and transform to dataframe
    """
    assert result.is_succeeded()
    columns = result.keys()
    d: Dict[str, list] = {}
    for col_num in range(result.col_size()):
        col_name = columns[col_num]
        col_list = result.column_values(col_name)
        d[col_name] = [x.cast() for x in col_list]
    return pd.DataFrame.from_dict(d, orient='columns')

def bfs(client, start_vertex_id):
    visited = {start_vertex_id}
    queue = [start_vertex_id]
    while queue:
        # 取出队列的第一个顶点
        vertex_id = queue.pop(0)
        print(f'Visited: {vertex_id}')
        # 查询该顶点的邻居
        query = f"GO FROM \"{vertex_id}\" OVER * BIDIRECT YIELD dst(edge);"
        print(query)
        result = client.execute(query)
        print(f'Result:{result}')
        if result.is_succeeded():
            result_df = result_to_df(result)
            print("df_result:",result_df)
            for neighbor_id in result_df['dst(EDGE)']:
                #print(f'Neighbor: {neighbor_id}')
                if neighbor_id not in visited:
                    visited.add(neighbor_id)
                    queue.append(neighbor_id)
        else:
            print(f"Query failed: {result.error_msg()}")

# define a config
config = Config()

# init connection pool
connection_pool = ConnectionPool()

# if the given servers are ok, return true, else return false
ok = connection_pool.init([('127.0.0.1', 9669)], config)

# option 2 with session_context, session will be released automatically
with connection_pool.session_context('root', 'nebula') as session:
    session.execute('USE demo_basketballplayer')
    # result = session.execute('GO FROM \"player100\" OVER follow YIELD dst(edge)')
    # df = result_to_df(result)
    # print(df)
    bfs(session, 'player100')

connection_pool.close()
