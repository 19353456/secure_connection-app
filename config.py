import os

class Config:
    SECRET_KEY = os.environ.get('64c69db83fa9c435419691620d7453d5f16fb7590744c70a8967351fb1e0d494') or  'wmepcksa'
    SQLALCHEMY_DATABASE_URI = 'postgresql://mannan:your_password@localhost/disease_info'
    SQLALCHEMY_TRACK_MODIFICATIONS = False
