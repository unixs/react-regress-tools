import { Repository } from "nodegit";
import { resolve } from "path";
import madge from 'madge';

async function getAffectedFiles(repo_path: string, hash: string): Promise<string[]> {
  const files: string[] = [];

  const repo = await Repository.open(repo_path);
  const from = await repo.getCommit(hash);
  const to = await repo.getHeadCommit();

  const fromTree = await from.getTree();
  const toTree = await to.getTree();

  const diff = await toTree.diff(fromTree);

  for (const patch of await diff.patches()) {
    const fileDiff = patch.newFile();
    const path = fileDiff.path();

    files.push(path);
  }

  return files;
}

function getRepoPath() {
  const REPO_PATH = '../../study-poc'

  return resolve(REPO_PATH);

}

function getLastCommit() {
  return '60bf46944c466a7b67981e1fdd7a7999acca061a';
}

function normalizePathToRepoRoot(file: string) {

}

async function getDepsForFile(file: string) {
  const result = new Map<string, string[]>();

  const deps = await madge(file, {
    excludeRegExp:[ /^.*\.scss$/ ],
  });

  const depsObject = deps.obj();

  for (const depPath of Object.keys(depsObject)) {
    result.set(depPath, depsObject[depPath]);
  }

  return result;
}

export {
  getAffectedFiles,
  getRepoPath,
  getLastCommit,
  getDepsForFile
};
