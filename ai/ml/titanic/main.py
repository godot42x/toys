import os
from statistics import LinearRegression
import time

from sklearn.model_selection import train_test_split
from torch import mode, norm


def install_packages(names):
    start_time = time.time()
    import importlib.metadata
    import subprocess
    import sys

    def install_packages(names):
        for name in names:
            try:
                _version = importlib.metadata.version(name)
                # print(f"{name} already installed ({_version})")
            except importlib.metadata.PackageNotFoundError:
                subprocess.run([sys.executable, "-m", "pip", "install", name],
                               check=True)

    install_packages(names)

    print(f"Package installation took {time.time() - start_time:.2f} seconds")


install_packages([
    'numpy',
    'pandas',
    'scikit-learn',
    'matplotlib',
    'torch',
    'seaborn',
    'lightgbm',
])

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns


def test_pd():
    data = {
        'name': ['Alice', 'Bob', 'Charlie'],
        'grade': ['1', '2', '3'],
        'score': [3, 2.5, 3],
    }
    df = pd.DataFrame(data)
    print("Pandas DataFrame:")
    print(df.describe())

    # plt.bar(df.name, df.grade, label='grade', alpha=0.5)
    # plt.bar(df.name, df.score, label='score', alpha=0.5)
    # plt.show()

    sns.barplot(x='name', y='score', hue='grade', data=df)
    plt.show()


# test_pd()


def test_plot():
    d = sns.load_dataset("titanic")

    print(d.columns)
    print(len(d))
    print("survived counts:", d.survived.value_counts())
    print("survived rate:", d.survived.mean())

    d['age_range'] = pd.cut(d['age'], bins=[0, 10, 30, 60, 80])
    print(d.age_range.value_counts())

    # one figure
    # sns.barplot(d, x="age_range", y="survived", hue='age_range')
    # plt.show()

    # multi figure by sex
    grid = sns.FacetGrid(d, col='sex', hue='survived')
    grid.map(plt.hist, 'age', bins=4, alpha=0.7)
    grid.add_legend(title='Survived')
    # grid.set_titles(col_template="{col_name} Passenger")
    plt.show()

    # multi figure by  pclass (the ticket class of the passenger)
    grid = sns.FacetGrid(d,
                         col='pclass',
                         hue='survived',
                         palette=['#2b8cbe', '#f03b20'])
    grid.map(plt.hist, 'age', bins=4, alpha=0.8, edgecolor='k')
    grid.add_legend(title='Survived')
    plt.show()


import sklearn

data = sns.load_dataset("titanic")

# normalize data
print(data[0:5])
# data.drop('class')  # pclass is the same as class
# data.drop('alive')
# data.alone.replace({True: 1, False: 0}, inplace=True)
# data.deck.replace({np.nan: '0', 'A': 1, 'B': 2, 'C': 3}, inplace=True)
# data.embarked.replace({'S': 0, 'C': 1, 'Q': 2, np.nan: 3}, inplace=True)
# data.age.fillna(data.age.median(), inplace=True)
# data.sex.replace({'male': 0, 'female': 1}, inplace=True)
# data.drop('who')  # same as sex
norm_data = pd.DataFrame({
    'survived': data.survived,
    'sex': data.sex == 'female',
    'age': data.age.fillna(data.age.median()),
    'pclass': data.pclass,
    'embarked': pd.factorize(data.embarked)[0],  # 转换任意类别数据为float
})

print(norm_data.corr())

#random_state 是控制打乱数据的随机数种子，传入整数会固定伪随机序列，从而保证每次调用
#  train_test_split 时得到相同的训练/测试划分。若传入 None，则使用系统随机性。
train_d, test_d = train_test_split(norm_data,
                                   test_size=0.2,
                                   random_state=42,
                                   shuffle=True)
# print(data.sex)


def linear_regression_example():
    "线性回归"
    from sklearn.linear_model import LogisticRegression

    model = LogisticRegression(random_state=42)
    # X_train = pd.DataFrame({
    #     'age': train_d.age.fillna(0),
    #     'sex': train_d.sex == 'male',
    #     'pclass': train_d.pclass,
    #     # don't put y here, as put the answer of the model
    # })
    X_train = train_d.drop(columns='survived')
    print(X_train.shape)
    Y_train = train_d['survived']
    model.fit(X_train, Y_train)

    # X_test = pd.DataFrame({
    #     'age': test_d.age.fillna(0),
    #     'sex': test_d.sex == 'male',
    #     'pclass': test_d.pclass,
    # })
    X_test = test_d.drop(columns='survived')
    Y_test = test_d['survived']
    Y_pred = model.predict(X_test)

    # 评估模型效果
    rst = model.score(X_test, Y_test)
    print(rst)

    # 视觉分析预测效果
    last_df = pd.DataFrame({
        'Y_test': Y_test,
        'Y_pred': Y_pred,
        'age': X_test['age'],
    })
    last_df['age_range'] = pd.cut(last_df['age'], bins=[0, 10, 30, 60, 80])

    sns.barplot(last_df, x='age_range', y='Y_pred', hue='Y_test', alpha=0.5)
    plt.show()


def decision_tree_classifier():
    "决策树分类器, 非常容易过拟合"
    from sklearn.tree import DecisionTreeClassifier

    model = DecisionTreeClassifier(
        random_state=42,
        class_weight=
        'balanced',  # 对于类别不平衡的数据集，使用 balanced 可以帮助模型更好地学习少数类的特征，从而提高整体的分类性能。
    )

    X_train = train_d.drop(columns='survived')
    Y_train = train_d['survived']

    X_test = test_d.drop(columns='survived')
    Y_test = test_d['survived']

    model.fit(X_train, Y_train)

    Y_pred = model.predict(X_test)

    rst = model.score(X_test, Y_test)
    print("use decision tree classifier:", rst)


# decision_tree_classifier()


def LGBM():
    "更优的 决策树分类器"
    from lightgbm import LGBMClassifier

    model = LGBMClassifier(
        random_state=42,
        class_weight=
        'balanced',  # 对于类别不平衡的数据集，使用 balanced 可以帮助模型更好地学习少数类的特征，从而提高整体的分类性能。
        max_leaves=12,
        max_depth=5,
        n_estimators=30,
        # learning_rate=0.1,
    )

    X_train = train_d.drop(columns='survived')
    Y_train = train_d['survived']

    X_test = test_d.drop(columns='survived')
    Y_test = test_d['survived']

    model.fit(X_train, Y_train)

    Y_pred = model.predict(X_test)

    rst = model.score(X_test, Y_test)
    print("lgbm: ", rst)


LGBM()
