from flask import request
from flask_restful import Resource
import os
import subprocess

class CRIU(Resource):
    def get(self):
        return {"message": "Hello, World!"}

    def post(self):
        json_data = request.get_json(force=True)
        if not json_data:
               return {'message': 'No input data provided'}, 400

        os.system(" docker run -d --name looper --security-opt seccomp:unconfined busybox /bin/sh -c 'i=0; while true; do echo $i; i=$(expr $i + 1); sleep 1; done'")
        result = "CRIU Checkpoint"
        return {'status': "success", 'data': result}, 201
