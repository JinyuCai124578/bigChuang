from nebula3.gclient.net import ConnectionPool
from nebula3.Config import Config
import pandas as pd
import sys
from tqdm import tqdm
import time

def nGQL(ngql, print_reply = 0):
    res = session.execute(ngql)
    if res.is_succeeded():
        if print_reply:
            print(f"REPLY: {res}")
        return
    elif not res.is_succeeded():
        print(f"Query failed:{res.error_msg()}")
        sys.exit()

def load_vertex(df):
    total_rows = len(df)
    update_interval = int(total_rows * 0.1)  # 计算更新的步长
    progress_bar = tqdm(total=total_rows, desc="Loading vertices", unit="row")

    for index, row in df.iterrows():
        # 执行加载操作
        nGQL(f"INSERT VERTEX host(weight) VALUES {row['id']}:({row['weight']})")

        # 每达到更新步长时，更新进度条
        if index % update_interval == 0:
            progress_bar.update(update_interval)

    progress_bar.close()

def load_edge(df):
    total_rows = len(df)
    update_interval = int(total_rows * 0.1)  # 计算更新的步长
    progress_bar = tqdm(total=total_rows, desc="Loading edges", unit="row")

    for index, row in df.iterrows():
        # 执行加载操作
        nGQL(f"INSERT EDGE connection(dist, src_label_id, dst_label_id) VALUES {row['src_id']} -> {row['dst_id']}:({row['dist']}, {row['src_label_id']}, {row['dst_label_id']})")

        # 每达到更新步长时，更新进度条
        if index % update_interval == 0:
            progress_bar.update(update_interval)

    progress_bar.close()
    
config = Config()

# init connection pool
connection_pool = ConnectionPool()

# if the given servers are ok, return true, else return false
ok = connection_pool.init([('127.0.0.1', 9669)], config)


# option 2 with session_context, session will be released automatically
start_time = time.time()
with connection_pool.session_context('root', 'nebula') as session:
    #create space
    nGQL("CREATE SPACE IF NOT EXISTS p2p_network(vid_type = INT64)", 1)
    print("create success")
    nGQL("USE p2p_network", 1)
    
    #create tag and edge
    nGQL("CREATE TAG IF NOT EXISTS host(weight int)", 1)
    nGQL("CREATE EDGE IF NOT EXISTS connection(dist int, src_label_id int, dst_label_id int)", 1)

    #insert vertex
    df_vertex = pd.read_csv("p2p-31_property_v_0")
    df_edge = pd.read_csv("p2p-31_property_e_0")
    load_vertex(df_vertex)
    print("SUCCESSFULLY LOAD VERTEX!")
    load_edge(df_edge)
    print("SUCCESSFULLY LOAD EDGE")

end_time = time.time()
# 计算执行时间
execution_time = end_time - start_time
print(f"csv载图时间为: {execution_time} 秒")

connection_pool.close()
