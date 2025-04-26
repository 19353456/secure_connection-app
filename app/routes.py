from flask import render_template
from app import app
from app.models import Disease

@app.route('/')
def home():
    diseases = Disease.query.all()
    return render_template('home.html', diseases=diseases)
