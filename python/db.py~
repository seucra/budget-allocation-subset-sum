from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from models import Base

# Replace 'user1' and 'password1' with your Postgres credentials
DATABASE_URL = "postgresql://user1:password1@localhost/budgetdb"

engine = create_engine(DATABASE_URL)
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

def init_db():
    Base.metadata.create_all(bind=engine)

def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()
