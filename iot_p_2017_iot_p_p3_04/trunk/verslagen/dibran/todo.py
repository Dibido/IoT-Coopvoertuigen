from flask import Flask, jsonify, abort, make_response, request, url_for, g
from sqlite3 import dbapi2 as sqlite3

app = Flask(__name__)

tasks = [
    {
        'id' : 1,
        'title' : "Leer ReST API's schrijven",
        'description': "Zelf ReST API's schrijven is geweldig!",
        'done' : False
    },
    {
        'id' : 2,
        'title' : "Leer een beetje python",
        'description' : "De wereld bestaat niet alleen uit C",
        'done' : False
    }
    ]

def get_db():
    if not hasattr(g, 'sqlite_d'):
        g.sqlite_db = connect_db()
    return g.sqlite_db

def connect_db():
    rv = sqlite3.connect('todo.db')
    rv.row_factory = sqlite3.Row
    return rv

def close_db(error):
    if hasattr(g, 'sqlite_db'):
        g.sqlite_db.close()

def last_id():
    db = get_db()
    cur = db.execute('select last_insert_rowid() from items')
    rows = cur.fetchall()
    return rows[0][0]

def retrieve_task(task_id):
    db = get_db()
    cur = db.execute("select * from items where id = ?", (task_id, ))
    rows = cur.fetchall()
    tasks = []
    for row in rows:
        tasks.append({'id' : row[0], 'title' : row[1], 'description' : row[2], 'done' : row[3] == 1})
    return tasks

def make_public_task(task):
    new_task = {}
    for field in task:
        if field == 'id':
            new_task['uri'] = url_for('get_task', task_id=task['id'], _external=True)
        else:
            new_task[field] = task[field]
        return new_task

@app.route('/todo/tasks', methods=['GET'])
def get_tasks():
    db = get_db()
    cur = db.execute('select * from items order by id')
    rows = cur.fetchall()

    tasks = []
    for row in rows:
        tasks.append({'id': row[0], 'title': row[1], 'description': row[2], 'done': row[3] == 1})
    return jsonify({'tasks': [make_public_task(task) for task in tasks]})

@app.route('/todo/tasks/<int:task_id>', methods=['GET'])
def get_task(task_id):
    task = retrieve_task(task_id)
    if len(task) == 0:
        abort(404)
    return jsonify({'task': task[0]})

@app.route('/todo/tasks', methods=['POST'])
def create_task():
    if not request.json or 'title' not in request.json:
        abort(400)
    db = get_db()
    cur = db.execute("insert into items (title, description, done) values (?,?,0)", ( request.json['title'], request.json.get('description', "default")))
    db.commit()
    tasks = retrieve_task(last_id())
    return jsonify({'tasks': [make_public_task(task) for task in tasks]})

@app.route('/todo/tasks/<int:task_id>', methods=['PUT'])
def update_task(task_id):
    task = [task for task in tasks if task['id'] == task_id]
    if len(task) == 0:
        abort(404)
    if not request.json:
        abort(400)
    if 'title' in request.json and not isinstance(request.json['description'], unicode):
        abort(400)
    if 'description' in request.json and not isinstance(request.json['done'], bool):
        abort(400)
    db = get_db()
    cur = db.execute("update items set title = ?, description = ?, done = ? where id = ?", (request.json.get('title', task[0]['title']), request.json.get('description', task[0]['description']), request.json.get('done'), task_id))
    db.commit();
    task = retrieve_task(task_id)
    if len(task) == 0:
        abort(404)
    return jsonify({'task': task[0]})

@app.route('/todo/tasks/<int:task_id>', methods=['DELETE'])
def delete_task(task_id):
    task = [task for task in tasks if task['id'] == task_id]
    if len(task) == 0:
        abort(404)
    db = get_db()
    cur = db.execute("delete from items where id = ?", (task_id, ))
    db.commit()
    return jsonify({'result': True})

@app.errorhandler(400)
def bad_request(error):
    return make_response(jsonify({'error':'Bad request'}), 400)

@app.errorhandler(404)
def not_found(error):
    return make_response(jsonify({'error': 'not found'}), 404)

if __name__ == '__main__':
    app.run(debug=True)
