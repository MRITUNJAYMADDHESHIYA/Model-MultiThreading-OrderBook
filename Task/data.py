import requests
import tempfile
import pandas as pd

url = "https://file.notion.so/f/f/f3d54618-4ee1-480d-b8f7-25c361e2c7b2/12d14740-f5b4-4ce9-9d4d-b9d0b3cd5548/data.parquet?table=block&id=6fa5d867-4063-4844-aebb-4be60a25af39&spaceId=f3d54618-4ee1-480d-b8f7-25c361e2c7b2&expirationTimestamp=1764360000000&signature=wi3c0TpcRhYBT-U1B96Nw6-m3e2vU_wKHRpw45ZUmpA&downloadName=data.parquet"

r = requests.get(url)
with open("data.parquet", "wb") as f:
    f.write(r.content)

df = pd.read_parquet("data.parquet")
print(df)
