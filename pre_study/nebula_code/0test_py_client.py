from nebula3.gclient.net import ConnectionPool
from nebula3.Config import Config
# Define the connection configuration
config = Config()
config.max_connection_pool_size = 10
# Service address and port
host = '127.0.0.1'
port = 9669
# Initialize connection pool
connection_pool = ConnectionPool()
try:
    ok = connection_pool.init([(host, port)], config)
except Exception as e:
    print(f"Failed to initialize connection pool: {e}")
    exit(1)
if not ok:
    print("Failed to connect to Nebula Graph services.")
    exit(1)
# Connect to Nebula Graph with username and password
user_name = 'root'
password = 'nebula' # Replace with your password
try:
    session = connection_pool.get_session(user_name, password)
    print("Connection successful!")
except Exception as e:
    print(f"Failed to create session: {e}")
    connection_pool.close()
    exit(1)

# Execute a command
try:
    resp = session.execute('SHOW SPACES')
    print(resp)
except Exception as e:
    print(f"Failed to execute command: {e}")

# Close session and connection pool
session.release()
connection_pool.close()

