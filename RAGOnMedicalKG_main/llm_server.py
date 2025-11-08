# coding = utf-8
import os
import re
from tqdm import tqdm
import requests
import json
import time
from openai import OpenAI


class ModelAPI():
    def __init__(self, MODEL_URL):
        self.url = MODEL_URL
        return

    def send_request(self, message, history):
        data = json.dumps({"message":message, "history":history})
        headers = {'Content-Type': 'application/json'}
        try:
            res = requests.post(self.url, data=data, headers=headers)
            print(res)
            predict = json.loads(res.text)["output"][0]
            history = json.loads(res.text)["history"]
            return predict, history
        except Exception as e:
            print("request error", e)
            return "", []

    ## 防止并不稳定，需要多次访问
    def chat(self, query, history=[]):
        message = [{"role": "user", "content": query}]
        count = 0
        response = ''
        history = []
        while count <=10:
            try:
                count +=1
                response, history = self.send_request(message, history)
                if response:
                    return response, history
            except Exception as e:
                print('Exception:', e)
                time.sleep(1)
        return response, history


class OpenAIModelAPI:
    def __init__(self, base_url,api_key):
        self.client = OpenAI(base_url=base_url, api_key=api_key)

    def send_request(self, messages):
        try:
            completion = self.client.chat.completions.create(
                model="gpt-4.1",  # 或者使用你有访问权限的模型，例如 "gpt-3.5-turbo"
                messages=messages
            )
            response = completion.choices[0].message.content
            # 假设 history 不是由 API 直接返回，需要自行管理
            history = messages + [{"role": "assistant", "content": response}]
            return response, history
        except Exception as e:
            print("Request error:", e)
            return "", []

    def chat(self, query, history=[]):
        message = [{"role": "user", "content": query}]
        # 将新消息添加到历史记录中
        messages = history + message
        response, history = self.send_request(messages)
        return response, history
    
class PuyuModelAPI():
    def __init__(self, MODEL_URL='https://chat.intern-ai.org.cn/api/v1/chat/completions'):
        self.url = MODEL_URL
        self.header={
                        'Content-Type':'application/json',
                        "Authorization":"Bearer eyJ0eXBlIjoiSldUIiwiYWxnIjoiSFM1MTIifQ.eyJqdGkiOiI1MDIxMTAxNyIsInJvbCI6IlJPTEVfUkVHSVNURVIiLCJpc3MiOiJPcGVuWExhYiIsImlhdCI6MTc0Mjk5MTUwOCwiY2xpZW50SWQiOiJlYm1ydm9kNnlvMG5semFlazF5cCIsInBob25lIjoiMTc3NjUxMjI5MDIiLCJvcGVuSWQiOm51bGwsInV1aWQiOiIyODI4ZDIyMi04MDQwLTRhMTItOTI1Yi1hYjkyMjNhM2E1MzQiLCJlbWFpbCI6ImNhaV9qaW55dUBzanR1LmVkdS5jbiIsImV4cCI6MTc1ODU0MzUwOH0.cWGLo7od_5-rdarrS3CmL5dW3Fe9QV2RDLyrliptl7FpJ0QodG0eekWHiBBuFl_HrLgTeRoUHTC35lEKCwskkQ"
                    }
        

    def send_request(self, message, history):
        data = json.dumps({"message":message, "history":history})
        headers = {'Content-Type': 'application/json'}
        try:
            res = requests.post(self.url, data=data, headers=headers)
            print(res)
            predict = json.loads(res.text)["output"][0]
            history = json.loads(res.text)["history"]
            return predict, history
        except Exception as e:
            print("request error", e)
            return "", []

    def chat(self, query, history=[]):
        data = {
                    "model": "internlm2.5-latest",  
                    "messages": [{
                        "role": "user",
                        "text": query
                    }],
                    "n": 1,
                    "temperature": 0.0,
                    "top_p": 0.9
                }
        res = requests.post(self.url, headers=self.header, data=json.dumps(data))
        if "choices" in res.json():
            return res.json()["choices"][0]["message"]["content"],res
        else:
            return None,res

        


if __name__ == '__main__':
    model = PuyuModelAPI()
    res= model.chat(query="你叫啥", history=[])
    print(res)
