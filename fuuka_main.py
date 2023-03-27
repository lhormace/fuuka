import openai
import sys
import fuuka_settings
import const

openai.api_key = const.OPEN_AI_KEY

def generate_answer(prompt):
    print(prompt)
    response = openai.ChatCompletion.create(
        model="gpt-3.5-turbo",
        messages=[
            {"role": "user", "content": prompt}, #※1後述
        ]
    )
    return response

while True:
    print("【質問を入れてください】", end="")
    question = input()
    if (question == ''):
        print("何も入力されなかったので、プログラムを終了します。")
        sys.exit()
    answer = generate_answer(question)
    print(answer["choices"][0]["message"]["content"]) #返信のみを出力
