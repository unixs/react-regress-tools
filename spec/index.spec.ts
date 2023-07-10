import { resolve } from "path";
import { getAffectedFiles, getDepsForFile, getLastCommit, getRepoPath } from "../src";

describe("context", () => {
  it('last commit', () => {
    const lastCommit = getLastCommit();

    expect(typeof lastCommit).toBe('string');
    expect(lastCommit.length).toBe(40);
  });

  it('repo path', () => {
    const path = getRepoPath();

    expect(typeof path).toBe('string');
    expect(path.length).toBeGreaterThan(0);
  });
});

describe('examples', () => {
  it('affected files', async () => {
    const repoPath = getRepoPath();
    const lastCommit = getLastCommit();
    const result = await getAffectedFiles(repoPath, lastCommit);

    expect(result.length).toBeGreaterThan(0);
  }, 7000);

  it('get dependency tree', async () => {
    const component = 'src/components/Channel/Course/Course.jsx';
    const repoPath = getRepoPath();
    const path = resolve(repoPath, component);

    const deps = await getDepsForFile(path);

    expect(deps).toBeTruthy();
  }, 10000);
});
