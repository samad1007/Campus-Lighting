# This is a sample Python script.
import asyncio
import websockets
import json
async def test():
    while True:
        async with websockets.connect('wss://vurzcp9ti8.execute-api.ap-south-1.amazonaws.com/production') as websocket:
            x = input("Enter Message: ")
            dic = {"action": "sendmessage", "message": "{}".format(x)}
            await websocket.send(json.dumps(dic))
            response = await websocket.recv()
            print(response)
asyncio.get_event_loop().run_until_complete(test())
# asyncio.get_event_loop().run_forever()